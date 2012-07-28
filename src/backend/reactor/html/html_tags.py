
import htmlentitydefs as _e 
import subprocess as _subprocess
import re as _re
import sys as _sys

from html.html_constants import *
from html.html_path import tag_path as _tag_path

__all__ = (
	'Title', 'Param', 'Html', 
	'Tfoot', 'Var', 'Samp', 
	'Body', 'Basefont', 'Big', 
	'Object', 'Base', 'Br', 
	'Strong', 'Legend', 'Ol', 
	'Textarea', 'P', 'Div', 
	'Dir', 'Pre', 'Font', 
	'Select', 'Noframes', 'Sub', 
	'Area', 'Bdo', 'Label', 
	'Sup', 'Head', 'Option', 
	'Form', 'Hr', 'Link', 
	'Abbr', 'Ul', 'S', 
	'Iframe', 'Em', 'H2', 
	'H3', 'H1', 'H6', 
	'Kbd', 'H5', 'Meta', 
	'Style', 'Img', 'Dfn', 
	'Input', 'Thead', 'Script', 
	'B', 'Center', 'Isindex', 
	'Del', 'Small', 'Code', 
	'Frame', 'Ins', 'Noscript', 
	'Span', 'Menu', 'Tt', 
	'Tr', 'Tbody', 'Li', 
	'H4', 'Th', 'Strike', 
	'Td', 'Cite', 'Map', 
	'Dl', 'Blockquote', 'Fieldset', 
	'Dd', 'Address', 'Optgroup', 
	'Dt', 'A', 'Colgroup', 
	'I', 'Button', 'Q', 
	'Caption', 'Applet', 'U', 
	'Col', 'Frameset', 'Acronym', 
	'Table', 
	
	##
	'TOP_LEVEL_ELEMENTS', 'HEAD_ELEMENTS', 
	'GENERIC_BLOCK_LEVEL_ELEMENTS', 'LISTS', 'TABLES', 
	'FORMS', 'SPECIAL_INLINE_ELEMENTS', 'PHRASE_ELEMENTS', 
	'FONT_STYLE_ELEMENTS', 'FRAMES', 'INLINE_ELEMENTS', 
	'BLOCKLEVEL_ELEMENTS', 
	
	## 
	'HtmlBase', 'TagBase', 'GenericTagBase',
	
	##
	'Text', 'Raw', 'Comment', 'SgmlDecl', 'Doctype', 
	'PI', 
	
	##
	'add_attrs', 'new_tag', 'set_verbosity', 'html_tidy', 'escape_string', 'unescape_string',
	
	##
	'HTML_QUIET', 'HTML_WARN', 'HTML_STRICT', 'HTML_SHUTUP_TIDY'
	)

HTML_QUIET = 0
HTML_WARN = 1
HTML_STRICT = 2
HTML_SHUTUP_TIDY = 64
_MASK_VERBOSITY = HTML_WARN | HTML_STRICT
class _VERBOSITY(object):
		def __init__(self):
			self.value = HTML_WARN
			self.tidy = 0
_VERBOSITY = _VERBOSITY()

#***********************************************
# some functions
#***********************************************

def set_verbosity(verbosity):
	_VERBOSITY.value = verbosity & _MASK_VERBOSITY
	_VERBOSITY.tidy = verbosity & HTML_SHUTUP_TIDY
	error = verbosity & ~(_MASK_VERBOSITY | HTML_SHUTUP_TIDY)
	if error:
		raise ValueError('unknown verbosity flag: %s' % error)
	
	

def add_attrs(tag, *attrs):
	errors = []
	for i in attrs:
		i = i.lower()
		if i not in tag.supported_attrs:
			tag.supported_attrs.append(i)
		else:
			errors.append(i)
	return errors
	

def new_tag(name, tag_type=TT_GEN, has_endtag=True, attrs=ANY, can_contain=ANY):
	if attrs == ANY:
		attrs = [ANY]
	if can_contain == ANY:
		can_contain = [ANY]
	assert isinstance(attrs, list), 'attrs: list expected'
	assert isinstance(can_contain, list), 'can_contain: list expected'
	name = name.lower()
	return type(
				name, 
				(TagBase,),
				{
					'type': new_tag_type(name),
					'has_endtag': has_endtag,
					'can_contain': can_contain,
					'supported_attrs': attrs,
				}
			)


# TODO:
# had some problems on win98. subprocess.PIPIE didn't work
# 
def html_tidy(commandline, what):
	p = _subprocess.Popen(
				args=commandline, 
				#shell=True, 
				stdin=_subprocess.PIPE, 
				stdout=_subprocess.PIPE, 
				stderr=_subprocess.PIPE, 
				#close_fds=True # 1. not shure what it does 2. not available on windows
				# does it leave a open handle behind on *nix?
				)
	stdin, stderr = p.communicate(input=what)
	if not _VERBOSITY.tidy:
		if stderr:
			print >> _sys.stderr, stderr
	return stdin


#escape_ and unescape_
# taken from: atomef.py on http://www.intertwingly.net/blog/1581.html
def escape_string(string):
	for i in range(len(string) -1, -1, -1):
		n=ord(string[i])
		if n in _e.codepoint2name:
			string = '%s&%s;%s' % (string[:i], _e.codepoint2name[n], string[i+1:])
		elif n >= 128:
			string = '%s&#%d;%s' % (string[:i], n, string[i+1:])
	return string


def unescape_string(string):
	chunks = _re.split('&(#?\w+);', string)
	for i in range(1,len(chunks), 2):
		if chunks[i] in _e.name2codepoint:
			chunks[i] = unichr(_e.name2codepoint[chunks[i]])
		elif _re.match('#\d+$',chunks[i]):
			chunks[i] = unichr(int(chunks[i][1: ]))
	return "".join(chunks)

#***********************************************
# 
#***********************************************

class TagError(Exception):
	"""default error"""
	
	
class _AttrDict(dict):


	def _validate_attr(self, name, value):
		if not isinstance(value, basestring):
			raise TagError("attribute values must be strings: %s=%s" % (name, value))
		
		if _VERBOSITY.value and name not in self._supported_attrs:
			if self._supported_attrs != [ANY]:
				error = 'invalid attribute: %s' % name
				if _VERBOSITY.value == HTML_WARN:
					print >> _sys.stderr, 'warning: ' + error
				else:
					raise TagError(error)
	
	def __init__(self, supported_attrs, dict_):
		self._supported_attrs = supported_attrs
			
		if 'clss' in dict_:
			dict_['class'] = dict_['clss']
			del dict_['clss']
		for name, value in dict_.items():
			self._validate_attr(name, value)
		dict.__init__(self, dict_)
		
	def __setitem__(self, name, value):
		self._validate_attr(name, value)
		dict.__setitem__(self, name, value)
	
	def fromkeys(self, seq, value=""):
		for name in seq:
			self._validate_attr(name, value)
		dict.fromkeys(self, seq, value)
			
	def update(self, other):
		for name, value in other.items():
			self._validate_attr(name, value)
		dict.update(self, other)
		

class _ChildList(list):
	
	def __init__(self, tag, initlist):
		self._tag = tag
		list.__init__(self, [self._validate_child(i) for i in initlist])	
	
	
	def _validate_child(self, child):
			
		error = None
		
		if not self._tag.has_endtag:
			raise TagError('<%s> objects may not contain any tags' % self._tag.name)
	
		if isinstance(child, basestring):
			if self._tag.type in (TT_SCRIPT, TT_STYLE):
				child = Comment(child)
			else:
				child = Text(child)
		
		else:
			if child.type == TT_GEN_HTML_FILE:
				raise TagError('HtmlFile objects may not be contained in any tags')
			
			# avoid recursive adds
			if child.type not in GENERIC_ELEMENTS:
				if child.has_endtag:
					for i in child.walk():
						if i == self._tag:
							error = '<%s> object my not contain itsself' % self._tag.name
							raise TagError(error)
									
		# errorcheck
		if _VERBOSITY.value:
			if child.type in (TT_GEN_COMMENT, TT_GEN):
				pass
			
			elif child.type not in self._tag.can_contain:
				if self._tag.can_contain != [ANY]: 		# ignore
					error = '<%s> objects may not contain <%s> objects' % (self._tag.name, child.name)
				
				if error:	
					if _VERBOSITY.value == HTML_WARN:
						print >> _sys.stderr, 'warning: ' + error
					else:
						raise TagError(error)
		
		child._parent = self._tag
		return child
	
		
	def __add__(self, other):
			assert isinstance(other, list), 'list expected'
			other = [self._validate_child(i) for i in other]
			list.__add__(self, other)
			return self
			
	def __iadd__(self, other):
		assert isinstance(other, list), 'list expected'
		other = [self._validate_child(i) for i in other]
		list.__iadd__(self, other)
		return self
			
	def __setitem__(self, i, other):
		other = self._validate_child(other)
		list.__setitem__(self, i, other)
	
	def __setslice__(self, i, j, other):
		other = [self._validate_child(i) for i in other]
		list.__setslice__(self, i, j, other)
		
	def append(self, other):
		other = self._validate_child(other)
		list.append(self, other)
	
	def insert(self, i, other):
		other = self._validate_child(other)
		list.insert(self, i, other)

	def extend(self, other):
		if not isinstance(other, basestring):
			try:
				other = [self._validate_child(i) for i in other]
			except: pass
		else:
			other = self._validate_child(other)
		list.extend(self, other)


	def __mul__(self, num):
		raise NotImplementedError('__mul__() is not implemented')
	
	def __rmul__(self, num):
		raise NotImplementedError('__rmul__() is not implemented')

#***********************************************
# base classes
#***********************************************

class HtmlBase(object): pass

class GenericTagBase(HtmlBase): pass

class TagBase(HtmlBase):
	
	def __init__(self, **attrs):
		self.attrs = _AttrDict(self.supported_attrs, attrs)		
		self.children = _ChildList(self, [])
		self._parent = None
		
	# prop attrs
	def _get_attrs(self):
		return self.__attrs
	def _set_attrs(self, attrs):
		assert isinstance(attrs, dict), 'attrs: dict expected'
		self.__attrs = _AttrDict(self.supported_attrs, attrs)	
	def _del_attrs(self):
		self.__attrs = _AttrDict(self.supported_attrs, {})	
	attrs = property(_get_attrs, _set_attrs, _del_attrs)
		
	# prop children
	def _get_children(self):
		return self._children
	def _set_children(self, children):
		assert isinstance(children, list), 'children: list expected'
		self._children = _ChildList(self, children)
	def _del_children(self):
		self.__children = _ChildList(self, [])
	children = property(_get_children, _set_children, _del_children)
	
	# prop name
	def _get_name(self):
		return TAG_NAMES[self.type]
	name = property(_get_name, None, None)
	
	# prop parent
	def _get_parent(self):
		return self._parent
	parent = property(_get_parent, None, None)
	
	
	def __add__(self, other):
		self.children += others
		return self
	
	
	
	def __call__(self, *others):
		self.children += list(others)
		return self
	
	
	def copy(self):
		tag = self.__class__(**self.attrs)
		tag.children = [i.copy() for i in self.children]
		return tag
	
	
	def path(self, path):
		return _tag_path(self, path)
	
		
	def save(self, outpath=None, tidy=False):
		
		def format_endtag(tag):
				return '</%s>' % tag.name
									
		def format_starttag(tag):
			attrs = []
			for name, value in tag.attrs.items():
				if not value:
					attrs.append(value)		# set as flag
				else:
					attrs.append('%s="%s"' % (name, value))
			if attrs:
				return '<%s %s>' % (tag.name, ' '.join(attrs))
			else:
				return '<%s>' % tag.name
	
		data = ''
		for step, tag in self.walk(report=True):
			
			if tag.type == TT_GEN_HTML_FILE:
				continue
			
			if tag.type not in GENERIC_ELEMENTS:
				if step == 0:
					data+= format_starttag(tag)
				elif step == 1:
					data += format_starttag(tag)
				elif step == -1:
					if tag.has_endtag:
						data += format_endtag(tag)
			else:
				data += tag.value
					
		if tidy:	# let some tidylib do the dirty work
			data = html_tidy(tidy, data)
		
		if outpath:
			fp = open(outpath, 'w')
			try: fp.write(data)
			finally: fp.close()
		else:
			return data
	
	
	def walk(self, report=False):
				
		if report:
			def tag_walker(tag):
				
				if tag.has_endtag:
					yield 1, tag
				else:
					yield 0, tag
				
				for i in tag.children:
					if i.type in GENERIC_ELEMENTS:
						yield 0, i
					else:
						for x in tag_walker(i):
							yield x
								
				if tag.has_endtag:
					yield -1, tag
		
		else:
			def tag_walker(tag):
				yield tag
				for i in tag.children:
					if i.type in GENERIC_ELEMENTS:
						yield i
					else:
						for x in tag_walker(i):
							yield x
					
								
		return iter(tag_walker(self))
			
	
#***********************************************
# generic tags
#***********************************************

class Text(GenericTagBase):
	type = TT_GEN_TEXT
	
	def __init__(self, value):
		self.value = value
		self._parent = None
	
	def _get_name(self):
		return TAG_NAMES[self.type]
	name = property(_get_name, None, None)
	
	def _get_parent(self):
		return self._parent
	parent = property(_get_parent, None, None)
	
	def _get_value(self):
		return self.__value
	def _set_value(self, value):
		self.__value = escape_string(value)
	def _del_value(self):
		self.__value = ''
	value = property(_get_value, _set_value, _del_value)
	
	def copy(self):
		return self.__class__(self.value)


class Raw(GenericTagBase):
	type = TT_GEN_RAW
	
	def __init__(self, value):
		self.value = value
		self._parent = None
	
	def _get_name(self):
		return TAG_NAMES[self.type]
	name = property(_get_name, None, None)
	
	def _get_parent(self):
		return self._parent
	parent = property(_get_parent, None, None)
	
	def _get_value(self):
		return self.__value
	def _set_value(self, value):
		self.__value = value
	def _del_value(self):
		self.__value = ''
	value = property(_get_value, _set_value, _del_value)
	
	def copy(self):
		return self.__class__(self.value)



class Comment(GenericTagBase):
	type = TT_GEN_COMMENT
	
	def __init__(self, value):
		self.value = value
		self._parent = None
	
	def _get_name(self):
		return TAG_NAMES[self.type]
	name = property(_get_name, None, None)
	
	def _get_parent(self):
		return self._parent
	parent = property(_get_parent, None, None)
	
	def _get_value(self):
		return self.__value
	def _set_value(self, value):
		self.__value = '<!-- %s -->' % value
	def _del_value(self):
		self.__value = ''
	value = property(_get_value, _set_value, _del_value)
	
	def copy(self):
		return self.__class__(self.value[5:-4])

	
class SgmlDecl(GenericTagBase):
	type = TT_GEN_SGMLDECL

	def __init__(self, value):
		self.value = value
		self._parent = None
	
	def _get_name(self):
		return TAG_NAMES[self.type]
	name = property(_get_name, None, None)
	
	def _get_parent(self):
		return self._parent
	parent = property(_get_parent, None, None)
	
	def _get_value(self):
		return self.__value
	def _set_value(self, value):
		self.__value = '<!%s>' % value
	def _del_value(self):
		self.__value = ''
	value = property(_get_value, _set_value, _del_value)

	def copy(self):
		return self.__class__(self.value[2:-1])


class Doctype(SgmlDecl):
	type = TT_GEN_DOCTYPE
		
	def __init__(self, type='loose', doctype=None):
		if doctype:
			SgmlDecl.__init__(self, 'doctype %s' % doctype)
		else:	
			SgmlDecl.__init__(self, 'doctype %s' % DOCTYPES[type.lower()])
	
	def _get_name(self):
		return TAG_NAMES[self.type]
	name = property(_get_name, None, None)
	
	def copy(self):
		return self.__class__(doctype=self.value[9:-1])

class PI(GenericTagBase):
	type = TT_GEN_PI

	def __init__(self, value):
		self.value = value
		self._parent = None
	
	def _get_name(self):
		return TAG_NAMES[self.type]
	name = property(_get_name, None, None)
	
	def _get_parent(self):
		return self._parent
	parent = property(_get_parent, None, None)
	
	def _get_value(self):
		return self.__value
	def _set_value(self, value):
		self.__value = '<?%s>' % value
	def _del_value(self):
		self.__value = ''
	value = property(_get_value, _set_value, _del_value)
	
	def copy(self):
		return self.__class__(self.value[2:-1])
			
			
'''
# not working with pythons HTMLParser

class Php(GenericTagBase):
	type = TT_GEN_PHP
	
	def __init__(self, value):
		self.value = value
		self._parent = None
	
	def _get_name(self):
		return 'php()' 
	name = property(_get_name, None, None)
	
	def _get_parent(self):
		return self._parent
	parent = property(_get_parent, None, None)
		
	def _get_value(self):
		return self.__value
	def _set_value(self, value):
		self.__value = '<?php %s?>' % value
	def _del_value(self):
		self.__value = ''
	value = property(_get_value, _set_value, _del_value)
'''
	
#**************************************
# tags (a-z)
#***************************************

class A(TagBase):
	type = TT_A
	has_endtag = True
	can_contain = INLINE_ELEMENTS[:	]
	can_contain.remove(TT_A)
	supported_attrs = ['href', 'name', 'rel', 'rev', 'type',
					'target', 'hreflang', 'charset',
					'accesskey', 'tabindex', 'shape',
					'coords', 'onfocus', 'onblur'	
					] + COMMON_ATTRIBUTES + COMMON_EVENTS

class Abbr(TagBase):
	type = TT_ABBR
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES[:] + COMMON_EVENTS

class Acronym(TagBase):
	type = TT_ACRONYM
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES[:] + COMMON_EVENTS

class Address(TagBase):
	type = TT_ADDRESS
	has_endtag = True
	can_contain = INLINE_ELEMENTS + [TT_P, ]
	# transitional + TT_P
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Applet(TagBase):
	type = TT_APPLET
	has_endtag = True
	can_contain = BLOCKLEVEL_ELEMENTS + INLINE_ELEMENTS
	supported_attrs = ['code', 'codebase', 'width', 'height',
					'archive', 'object', 'name', 'alt', 
					'align', 'hspace', 'vspace']

class Area(TagBase):
	type = TT_AREA
	has_endtag = False
	can_contain = ()
	supported_attrs = ['shape', 'coords', 'href', 'target', 'nohref',
					'alt', 'tabindex', 'onfocus', 'onblur'] + COMMON_EVENTS

class B(TagBase):
	type = TT_B
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Base(TagBase):
	type = TT_BASE
	has_endtag = False
	can_contain = []
	supported_attrs = ["href", "target"]

class Basefont(TagBase):
	type = TT_BASEFONT
	has_endtag = False
	can_contain = []
	supported_attrs = ["color", "face", 'id']

class Bdo(TagBase):
	type = TT_BDO
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ["dir", "lang"] + CORE_ATTRIBUTES

class Big(TagBase):
	type = TT_BIG
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Blockquote(TagBase):
	type = TT_BLOCKQUOTE
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	# trans: INLINE_ELEMENTS or BLOCKLEVEL_ELEMENTS
	# strict: BLOCKLEVEL_ELEMENTS or TT_SCRIPT
	supported_attrs = ['cite', ] + COMMON_ATTRIBUTES + COMMON_EVENTS

class Body(TagBase):
	type = TT_BODY
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS + GENERIC_ELEMENTS
	# strict: BLOCKLEVEL_ELEMENTS + (TT_SCRIPT, TT_INS, TT_DEL)
	supported_attrs = ['background', 'bgcolor', 'text', 'link', 
					'vlink', 'alink', 'onload', 'onunload'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS

class Br(TagBase):
	type = TT_BR
	has_endtag = False
	can_contain = []
	supported_attrs = ["clear", ] + CORE_ATTRIBUTES

class Button(TagBase):
	type = TT_BUTTON
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	can_contain.remove(TT_A)
	can_contain.remove(TT_INPUT)
	can_contain.remove(TT_SELECT)
	can_contain.remove(TT_TEXTAREA)
	can_contain.remove(TT_LABEL)
	can_contain.remove(TT_BUTTON)
	can_contain.remove(TT_IFRAME)
	can_contain.remove(TT_FORM)
	can_contain.remove(TT_ISINDEX)
	can_contain.remove(TT_FIELDSET)
	supported_attrs = ['name', 'value', 'type', 'disabled', 'accessskey', 'tabindex', 
	'onfocus', 'onblur'] + COMMON_EVENTS

class Caption(TagBase):
	type = TT_CAPTION
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align', ] + COMMON_ATTRIBUTES + COMMON_EVENTS
	
class Center(TagBase):
	type = TT_CENTER
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Cite(TagBase):
	type = TT_CITE
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Code(TagBase):
	type = TT_CODE
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Col(TagBase):
	type = TT_COL
	has_endtag = False
	can_contain = []
	supported_attrs = ['span', 'width', 'align', 'char', 'charoff', 'valign', 'nowrap'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS
	
class Colgroup(TagBase):
	type = TT_COLGROUP
	has_endtag = True
	can_contain = [TT_COL, ]
	supported_attrs = ['span', 'width', 'align', 'char', 'charoff', 'valign'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS
		
class Dd(TagBase):
	type = TT_DD
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Del(TagBase):
	type = TT_DEL
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['cite', 'datetime'] +  COMMON_ATTRIBUTES + COMMON_EVENTS
		
class Dfn(TagBase):
	type = TT_DFN
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Dir(TagBase):
	type = TT_DIR
	has_endtag = True
	can_contain  = [TT_UL, ]
	supported_attrs = ['compact', ] + COMMON_ATTRIBUTES + COMMON_EVENTS
		
class Div(TagBase):
	type = TT_DIV
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['align', ] + COMMON_ATTRIBUTES + COMMON_EVENTS

class Dl(TagBase):
	type = TT_DL
	has_endtag = True
	can_contain = [TT_DD, TT_DT]
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS
		
class Dt(TagBase):
	type = TT_DT
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Em(TagBase):
	type = TT_EM
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Fieldset(TagBase):
	type = TT_FIELDSET
	has_endtag = True
	can_contain = [TT_LEGEND, ] + INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Font(TagBase):
	type = TT_FONT
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['size', 'color', 'face'] + CORE_ATTRIBUTES + \
					INTERNAT_ATTRIBUTES 
	
class Form(TagBase):
	type = TT_FORM
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	can_contain.remove(TT_FORM)
	supported_attrs = ['action', 'method', 'enctype', 'accept-charset', 'target', 'onsubmit',
					'onreset'] + COMMON_ATTRIBUTES + COMMON_EVENTS
	
class Frame(TagBase):
	type = TT_FRAME
	has_endtag = False
	can_contain = []
	supported_attrs = ['name', 'src', 'longdesc', 'frameborder', 'framewidth', 
					'marginheight', 'noresize', 'scrolling'] + CORE_ATTRIBUTES

class Frameset(TagBase):
	type = TT_FRAMESET
	has_endtag = True
	can_contain = [TT_FRAME, TT_NOFRAMES]
	supported_attrs = ['rows', 'cols', 'onload'] + CORE_ATTRIBUTES
	
class H1(TagBase):
	type = TT_H1
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align'] + COMMON_ATTRIBUTES + COMMON_EVENTS
	
class H2(TagBase):
	type = TT_H2
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align'] + COMMON_ATTRIBUTES + COMMON_EVENTS

class H3(TagBase):
	type = TT_H3
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align'] + COMMON_ATTRIBUTES + COMMON_EVENTS

class H4(TagBase):
	type = TT_H4
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align'] + COMMON_ATTRIBUTES + COMMON_EVENTS

class H5(TagBase):
	type = TT_H5
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align'] + COMMON_ATTRIBUTES + COMMON_EVENTS

class H6(TagBase):
	type = TT_H6
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align'] + COMMON_ATTRIBUTES + COMMON_EVENTS

class Head(TagBase):
	type = TT_HEAD
	has_endtag = True
	can_contain = [TT_TITLE, TT_BASE, TT_ISINDEX, TT_SCRIPT, TT_STYLE, 
							TT_META, TT_LINK, TT_OBJECT]
	supported_attrs = ["profile", ] + INTERNAT_ATTRIBUTES

class Hr(TagBase):
	type = TT_HR
	has_endtag = False
	can_contain = []
	supported_attrs = ['align', 'noshade', 'size', 'width'] + \
					CORE_ATTRIBUTES + COMMON_EVENTS + COMMON_EVENTS
		
class Html(TagBase):
	type = TT_HTML
	has_endtag = True
	can_contain = [TT_HEAD, TT_BODY, TT_FRAMESET]
	# frameset: TT_FRAMESET
	supported_attrs = ['version',] + INTERNAT_ATTRIBUTES

class I(TagBase):
	type = TT_I
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Iframe(TagBase):
	type = TT_IFRAME
	has_endtag = True
	can_contain = COMMON_ATTRIBUTES + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['src', 'name', 'longdesc', 'width', 'height', 'align', 'frameborder', 
					'marginwidth', 'marginheight', 'scrolling'] + CORE_ATTRIBUTES

class Img(TagBase):
	type = TT_IMG
	has_endtag = False
	can_contain = []
	supported_attrs = ['src', 'alt', 'longdesc', 'width', 'height', 'usemap', 'ismap', 'align', 
					'border', 'hspace', 'vspace'] + COMMON_ATTRIBUTES + \
					COMMON_EVENTS

class Input(TagBase):
	type = TT_INPUT
	has_endtag = False
	can_contain = []
	supported_attrs = ['type', 'name', 'value', 'checked', 'size', 'maxlength', 'src', 'alt', 
					'usemap', 'align', 'disabled', 'readonly', 'accept', 'accesskey', 
					'tabindex', 'onfocus', 'onblur', 'onselect', 'onchange'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS

class Ins(TagBase):
	type = TT_INS
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['cite', 'datetime'] + COMMON_ATTRIBUTES + COMMON_EVENTS 

class Isindex(TagBase):
	type = TT_ISINDEX
	has_endtag = False
	can_contain = []
	supported_attrs = ['prompt', ] + CORE_ATTRIBUTES + INTERNAT_ATTRIBUTES

class Kbd(TagBase):
	type = TT_KBD
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Label(TagBase):
	type = TT_LABEL
	has_endtag = True
	can_contain = INLINE_ELEMENTS[:]
	can_contain.remove(TT_LABEL)
	supported_attrs = ['for', 'acesskey', 'onfocus', 'onblur'] + COMMON_ATTRIBUTES + \
	COMMON_EVENTS

class Legend(TagBase):
	type = TT_LEGEND
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['accessskey', 'align'] + COMMON_EVENTS
	
class Li(TagBase):
	type = TT_LI
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['type', 'value'] +COMMON_ATTRIBUTES + COMMON_EVENTS
	

class Link(TagBase):
	type = TT_LINK
	has_endtag = False
	can_contain = []
	supported_attrs = ['rel', 'rev', 'href', 'type', 'target', 'media', 'hreflang', 'charset'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS
	
class Map(TagBase):
	type = TT_MAP
	has_endtag = True
	can_contain =	[TT_AREA, ] + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['name', ] + COMMON_ATTRIBUTES

class Menu(TagBase):
	type = TT_MENU
	has_endtag = True
	can_contain = [TT_LI, ]
	supported_attrs = ['compact', ] + COMMON_ATTRIBUTES + COMMON_EVENTS

class Meta(TagBase):
	type = TT_META
	has_endtag = False
	can_contain = []
	supported_attrs = ['name', 'http-equiv', 'content', 'scheme'] + \
					INTERNAT_ATTRIBUTES

class Noframes(TagBase):
	type = TT_NOFRAMES
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	# frame: TT_BODY
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Noscript(TagBase):
	type = TT_NOSCRIPT
	has_endtag = True
	can_contain =  INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Object(TagBase):
	type = TT_OBJECT
	has_endtag = True
	can_contain = [TT_PARAM, ] + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['data', 'classid', 'archive', 'codebase', 'width', 'height', 'name', 
					'usemap', 'type', 'codetype', 'standby', 'tabindex', 'declare', 
					'align', 'border', 'hspace', 'vspace'] + COMMON_ATTRIBUTES + \
					COMMON_EVENTS
	
class Ol(TagBase):
	type = TT_OL
	has_endtag = True
	can_contain = [TT_LI, ]
	supported_attrs = ['type', 'start', 'compact'] + COMMON_ATTRIBUTES + \
	COMMON_EVENTS

class Optgroup(TagBase):
	type = TT_OPTGROUP
	has_endtag = True
	can_contain = [TT_OPTION, ]
	supported_attrs = ['label', 'disabled'] +	COMMON_ATTRIBUTES + COMMON_EVENTS

class Option(TagBase):
	type = TT_OPTION
	has_endtag = True
	can_contain = [TT_GEN_TEXT]
	supported_attrs = ['value', 'selected', 'disabled', 'label'] + COMMON_ATTRIBUTES + \
	COMMON_EVENTS

class P(TagBase):
	type = TT_P
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['align', ] + COMMON_ATTRIBUTES + COMMON_EVENTS

class Param(TagBase):
	type = TT_PARAM
	has_endtag = False
	can_contain = []
	supported_attrs = ['name', 'value', 'valuetype', 'type', 'id']

class Pre(TagBase):
	type = TT_PRE
	has_endtag = True
	can_contain = INLINE_ELEMENTS[:]
	can_contain.remove(TT_IMG)
	can_contain.remove(TT_OBJECT)
	can_contain.remove(TT_APPLET)
	can_contain.remove(TT_BIG)
	can_contain.remove(TT_SMALL)
	can_contain.remove(TT_SUB)
	can_contain.remove(TT_SUP)
	can_contain.remove(TT_FONT)
	can_contain.remove(TT_BASEFONT)
	supported_attrs = ['width'] + COMMON_ATTRIBUTES + COMMON_EVENTS

class Q(TagBase):
	type = TT_Q
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = ['cite', ] + COMMON_ATTRIBUTES + COMMON_EVENTS

class S(TagBase):
	type = TT_S
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Samp(TagBase):
	type = TT_SAMP
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Script(TagBase):
	type = TT_SCRIPT
	has_endtag = True
	can_contain = [TT_GEN_COMMENT, ]
	supported_attrs = ['type', 'langzage', 'src', 'charset', 'defer']

class Select(TagBase):
	type = TT_SELECT
	has_endtag = True
	can_contain = [TT_OPTGROUP, TT_OPTION]
	supported_attrs = ['name', 'multiple', 'size', 'disabled', 'tabindex', 'onfocus', 'onblur', 
					'onchange'] + COMMON_ATTRIBUTES + COMMON_EVENTS
		
class Small(TagBase):
	type = TT_SMALL
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Span(TagBase):
	type = TT_SPAN
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Strike(TagBase):
	type = TT_STRIKE
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Strong(TagBase):
	type = TT_STRONG
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Style(TagBase):
	type = TT_STYLE
	has_endtag = True
	can_contain = [TT_GEN_COMMENT, ]
	supported_attrs = ['type', 'media', 'title'] + INTERNAT_ATTRIBUTES

class Sub(TagBase):
	type = TT_SUB
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Sup(TagBase):
	type = TT_SUP
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Table(TagBase):
	type = TT_TABLE
	has_endtag = True
	can_contain = [TT_CAPTION, TT_COL, TT_COLGROUP, TT_THEAD, TT_TFOOT, 
						TT_TBODY, TT_TR]
	supported_attrs = ['border', 'summary', 'width', 'bordeder', 'frame', 'rules', 'cellspacing', 
					'cellpadding', 'align', 'bgcolor'] + COMMON_ATTRIBUTES + \
					COMMON_EVENTS

class Tbody(TagBase):
	type = TT_TBODY
	has_endtag = True
	can_contain = [TT_TR, ]
	supported_attrs = ['align', 'char', 'charoff', 'valign'] +	COMMON_ATTRIBUTES + \
	COMMON_EVENTS

class Td(TagBase):
	type = TT_TD
	has_endtag = True
	can_contain = INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['rowspan', 'colspan', 'headers', 'abbr', 'scope', 'axis', 'align', 'char',
					'charoff', 'valign', 'width', 'height', 'nowrap', 'bgcolor'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS

class Textarea(TagBase):
	type = TT_TEXTAREA
	has_endtag = True
	can_contain = [TT_GEN_TEXT, ]
	supported_attrs = ['name', 'rows', 'cols', 'disabled', 'readpnly', 'accesskey', 'tabindex',
					'onfocus', 'onblur', 'onselect', 'onchange'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS

class Tfoot(TagBase):
	_name = TT_TFOOT
	has_endtag = True
	can_contain = [TT_TR, ]
	supported_attrs = ['align', 'char', 'charoff', 'valign'] + COMMON_ATTRIBUTES + \
	COMMON_EVENTS

class Th(TagBase):
	type = TT_TH
	has_endtag = True
	can_contain =	INLINE_ELEMENTS + BLOCKLEVEL_ELEMENTS
	supported_attrs = ['rowspan', 'colspan', 'headers', 'abbr', 'scope', 'axis', 'align', 'char',
					'charoff', 'valign', 'width', 'height', 'nowrap', 'bgcolor'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS

class Thead(TagBase):
	type = TT_THEAD
	has_endtag = True
	can_contain = [TT_TR, ]
	supported_attrs = ['align', 'char', 'charoff', 'valign'] + COMMON_ATTRIBUTES + \
	COMMON_EVENTS

class Title(TagBase):
	type = TT_TITLE
	has_endtag = True
	can_contain = [TT_GEN_TEXT, ]
	supported_attrs = INTERNAT_ATTRIBUTES[:]

class Tr(TagBase):
	type = TT_TR
	has_endtag = True
	can_contain = [TT_TH, TT_TD]
	supported_attrs = ['align', 'char', 'charoff', 'valign', 'bgcolor'] + \
					COMMON_ATTRIBUTES + COMMON_EVENTS

class Tt(TagBase):
	type = TT_TT
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class U(TagBase):
	type = TT_U
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS

class Ul(TagBase):
	type = TT_UL
	has_endtag = True
	can_contain = [TT_LI, ]
	supported_attrs = ['type', 'compact'] + COMMON_ATTRIBUTES

class Var(TagBase):
	type = TT_VAR
	has_endtag = True
	can_contain = INLINE_ELEMENTS
	supported_attrs = COMMON_ATTRIBUTES + COMMON_EVENTS













