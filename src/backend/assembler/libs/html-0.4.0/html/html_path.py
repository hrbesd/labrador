
import re as _re

from html.html_tools import iter_anchored as _iter_anchored

#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

class PathError(Exception):
	"""default error"""


#***********************************************
# pattern for xpath component matching
#
# splits AAA/BBB"aaa/aaa"
# >> AAA
# >> BBB"aaa/aaa"
#***********************************************
_path_pat = _re.compile(r'''

(/{1,2})                                    # slash
(                                               #
    (?: [^/]*?  ".*?"   [^/]*)          # component containing a quoted part
|                                               # or
    (?: [^/]+)                              # component
)                                               #

''', _re.X)


#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
def _test():
	
	p = '/*'
	
	rx0 = _path_pat.match(p)
	if rx0 == None:
		raise 'invalid pattern'
	
	r = _path_pat.finditer(p)
	start = 0
	for match in r:
		print '('
		for i in match.groups():
			print '	%s,' % i
		print ')'
				
		if match.start() != start:
			raise 'invalid path patern position: %s' % start
		
		start = match.end()
	
#_test()

#*********************************************
# pattern for path components
# 
# splits 'td[1][@foo="bar"] into:
# td				group('name')
# [...][...]		group('attrs')
#*********************************************
_component_pat = _re.compile(r'''

^                                                     # optional name
    (?P<name>                                 #
        (?:  [a-zA-Z]+|\*  )	                   # name
    |                                                  # or 
        (?:  [a-zA-Z-]+ \(\)  )                # symbol()
    |                                                  # or
        (?:    \*)	                                   # *
    |                                                  # or
        (?:  \.\.)                                    # ..
    )?                                                #
    (?P<attrs>                                  # optional attributes
        (?:   \[   [^\[\]]*? \] )*	               # in braces
    )?
$

''', _re.X)

#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
def _test():
	
	p = 'aaa[not(@*)][1]'
	
	match = _component_pat.match(p)
	print '{'
	for name, value in match.groupdict().items():
		print '	%s: %s,' % (name, value)
	print '}'

#_test()

#************************************************
# pattern matching attributes
#
# splits [1][@foo="bar"][not(@*="baz")]
# 1								 group('index')
# [foo="bar"]			   group('attr')
#					   =		   group('value')
#   [not(@*="baz")] group('notattr')
#								   group('novalue')
#************************************************
_attr_pat = _re.compile(r'''

   \[																					   # [
		(																					#
			(?:  \s*  (?P<index>-?[0-9]+)  \s*  )				   # <-- index number
		|																				   # or
			(?:  @																		# @attr=value
				(?P<attr>[a-zA-Z_]+	| \*   )						  # <-- attr
				(?:  \s*=\s*														 # = 
					(?: \"|\')?														# lit or lita
						(?P<value>.*?)										   # <-- value
					(?: \"|\')?  )?												  # lit or lita
			)																				#
		|																				   # or
			(?:  not\(@															   # not(@attr=value)
				(?P<notattr>[a-zA-Z]+ | \*   )						 # <-- attr
				(?:  \s*=\s*														# =
					(?: \"|\')?													   # lit or lita
						(?P<notvalue>.*?)									 # <-- value
					(?: \"|\')?  )?												  # lit or lita
				\)																		  #
			)																				#
		)																					#
	\]																					  # ]

''', _re.X)
#,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

def _test():
	
	p = '[not(@*)][1]'
		
	enum = _attr_pat.finditer(p)
	
	print '('
	for i in enum:
		
		print '	{'
		for name, value in i.groupdict().items():
			print '		%s: %s,' % (name, value)
		print '	}'
	print ')'
	
#_test()


#**********************************************
#
#**********************************************


def iter_components(xpath):
	"""iterator over a path
	yields a dict containing the specs for the next component in turn
	the dict may contain one or more the following keys:
		anchor: anchor
		name: name 
		index: list[i1, i2, ...]
		attrs: list[(name, value), (...)]
		notattrs: list[(name, value), (...)]

	"""

	enum1 = _iter_anchored(_path_pat, xpath)
	for rx1 in enum1:
		if rx1 == None:
			error = '\n'.join((
			'\n	position: %s' % enum1.start(),
			'	invalid component: %s' % xpath[enum1.start() : enum1.end()]
			))
			raise PathError(error)
		else:
			cp_anchor, cp_component = rx1.groups()
									
			rx2 = _component_pat.match(cp_component)
			if rx2 == None:
				error = '\n'.join((
				'\n	position: %s' % rx1.start(),
				'	invalid component: %s' % xpath[enum1.start() : enum1.end()]
				))
				raise PathError(error)
				
			cp_name =  rx2.groupdict()['name'] 
			cp_attributes =rx2.groupdict()['attrs']
			
			index = []
			attrs = []
			notattrs = []
			if cp_attributes:
				enum3 = _iter_anchored(_attr_pat, cp_attributes)
				for rx3 in enum3:
					if rx3 == None:
						error = '\n'.join((
						'\n	position: %s' % rx1.start(),
						'	invalid component: %s%s' % (cp_anchor, cp_component),
						'	invalid attribute: %s' % attrs[enum3.start(): enum3.end()],
						))
						raise PathError(error)
					else:
						groupdict = rx3.groupdict()
						for name, value in groupdict.items():
							if value != None:
								if name == 'index':
									index.append(int(value))
								elif name == 'attr':
									  attrs.append((value, groupdict['value']))
								elif name == 'notattr':
									notattrs.append((value, groupdict['notvalue']))
									 
			yield {
						'anchor': cp_anchor,
						'name': cp_name,
						'index': index,
						'attrs': attrs,
						'notattrs': notattrs,
					}
	

def list_components(xpath):
	"""returns an xpath as list of components"""
	return [i for i in iter_components(xpath)]
	

def match_spec(tag, siblings, component):
	"""handles all supported pattern matching within components"""
	
	flag = True
	
	# match name
	if component['name'] != None:
		flag = False
		if component['name'] == '*':
			flag = True
		else:
			flag = component['name'] == tag.name
		if not flag:
			return False

	# match index
	if component['index']:
		flag = False
		if siblings:
			tag_siblings = [i for i in siblings if i.type == tag.type]
			for i in component['index']:
				try:
					n = tag_siblings.index(tag)
					if i >= 0:
						if n == i:
							flag = True
							break
					else:
						if len(tag_siblings) + i == n:
							flag = True
							break
				except: pass
		else:
			if 0 in component["index"] or -1 in component["index"]:
				flag = True
		if not flag:
			return False
	
	# match attrs
	if component['attrs'] and not hasattr(tag, "attrs"):
		return False
	
	
	if component['attrs']:
		flag = False	
		for name, value in component['attrs']:
					
			if name == '*':
								
				#									   # at least one attribute and
				#									   # every attribute found must have a value 
				# @*=*						  # (no flag attribute at all that is ;-)
				if value == '*':
					if tag.attrs:
						flag = True
						for attr_value in tag.attrs.values():   
							if not attr_value:
								flag = False
							break
												
				# @*								# at least one attribute
				elif value == None:
					if tag.attrs:
						flag = True
								
				#									   # at least one attribute and
				#									   # and at least one attribute must have
				# @*="value"				# the value "value"
				else:
					for attr_value in tag.attrs.values():	
						if attr_value.lower() == value:
							flag = True
							break
															
			else:
				#									   # attribute "name" with any value 
				# @name=*				   # (not any flag attribute that is
				if value == '*':
					for attr_name, attr_value in tag.attrs.items():
						if attr_name.lower() == name.lower():
							if attr_value:
								flag = True
							break
																															
				# @name="value"		 # attribute "name" with value "value"
				else:
					for attr_name, attr_value in tag.attrs.items():
						if attr_name.lower() == name.lower():
							if attr_value.lower() == value.lower():
								flag = True
							break
																								
		
			if not flag:
				return False
	
	# match not-attrs
	# not()
	if component['notattrs']:
		flag = False
		
		for name, value in component['notattrs']:
					
			if name == '*':
								
				#									   # at least one attribute and
				#									   # no attribute must have a value 
				# not(@*=*)				 # (only flag attributes allowed that is ;-)
				if value == '*':
					if tag.attrs:
						flag = True
						for attr_value in tag.attrs.values():   
							if attr_value:
								flag = False
								break
										
				# not(@*)						   # not any attribute at all
				elif value == None:
					flag = not tag.attrs
															
				#										   # at least one attribute but 
				# not(@*="value")		   # none may have the value "value"
				else:
					if tag.attrs:
						flag = True
						for attr_value in tag.attrs.values():   
							if attr_value.lower() == value.lower():
								flag = False
								break
													
			else:
				#										   # attribute "name" without value 
				# not(@name=*)			  # (a flag attribute that is ;-)
				if value == '*':
					for attr_name, attr_value in tag.attrs.items():
						if attr_name.lower() == name.lower():
							if not attr_value:
								flag = True
							break
					
																													
				#										   # attribute "name" may not 
				# not(@name="value")		# have value value "value"
				else:
					for attr_name, attr_value in tag.attrs.items():
						if attr_name.lower() == name.lower():
							if not attr_value.lower() == value.lower():
								flag = True
							break
										
		
			if not flag:
				return False
	
	# finally
	return flag

		


def tag_path(tag, xpath, out=None):
	"""xpath implementation"""
		
	if out == None:
		out = []
			
	if isinstance(xpath, basestring):
		components = xpath.lower()
		components = list_components(components)
	else:
		components = xpath
		
	try:
		last_component= components.pop() 
	except:
		error = 'no path specified: %s' % xpath
		raise PathError(error)
		
	if components:									  # recurse into subtree
		component = components.pop(0)
		rng = range(len(tag.children))
		sub_path = components + [last_component, ]
		
		if component['name'] == 'root()':
			
			if tag.parent:
				parent = tag.parent
				while parent:
					root = parent
					parent = parent.parent
			else:
				root = tag
			tag_path(root, sub_path[:], out=out)
		
		else:
			if component['anchor'] == '/':
				
				if component['name'] == '..':
					if tag.parent != None:
						tag_path(tag.parent, sub_path[:], out=out)
				
				else:
					for x in tag.children:
						if match_spec(x, tag.children, component):
							tag_path(x, sub_path[:], out=out)

			else:
				
				for x in tag.walk():
					parent = x.parent
					if parent:
						siblings = parent.children
					else:
						siblings = None
					if match_spec(x, siblings, component):
						tag_path(x, sub_path[:], out=out)


	else:									   # parse elements of tag
		
		if last_component['name'] == 'root()':
			
			parent = tag.parent
			if parent:
				while parent:
					out = [parent, ]
					parent = parent.parent
			else:   
				out = [tag, ]
			
		else:   
		
			if last_component['anchor'] == '/':
				
				if last_component['name'] == '..':
					if tag.parent != None:
						out.append(tag.parent)
				
				else:
					rng = range(len(tag.children))
					for x in tag.children:
						if match_spec(x, tag.children, last_component):
							out.append(x)
				
			else:   
				for x in tag.walk():
					parent = x.parent
					if parent:
						siblings = parent.children
					else:
						siblings = None
					if match_spec(x, siblings, last_component):
						out.append(x)

	return out



