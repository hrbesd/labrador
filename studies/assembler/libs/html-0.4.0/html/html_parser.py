
import HTMLParser

from html import html_tags
#:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::.


class ParserError(Exception): pass


class Parser(HTMLParser.HTMLParser):
	
	
	def __init__(self, doctype='loose'):
		HTMLParser.HTMLParser.__init__(self)

		self._doctype = doctype
		self.reset()
		
	
	def reset(self):
		HTMLParser.HTMLParser.reset(self)
		self._stack = []
		self._tags = []
				
	
	def feed_string(self, string):
		self.reset()
		HTMLParser.HTMLParser.feed(self, string)
		if self._stack:
			self._tags += self._stack
		return self._tags
		
	
	def feed_file(self, fpath):
		fp = open(fpath)
		try: tags = self.feed_string(fp.read())
		finally: fp.close()
		return tags
					
	
	def get_pos(self):
		return HTMLParser.HTMLParser.getpos(self)
		
	
	def push(self, tag):
		
		if hasattr(tag, 'has_endtag') and tag.has_endtag:
			if self._stack:
				self._stack[-1](tag)
			self._stack.append(tag)
		else:
			if self._stack:
				self._stack[-1](tag)
			else:
				self._tags.append(tag)
				
	
	def pop(self, tag_name):
		if self._stack:
			pop = None
			for n in reversed(range(len(self._stack))):
					stack_tag = self._stack[n]
					if stack_tag.name == tag_name:
							pop = n
							break
			else:
				raise 'unexpected endtag'
				
			if pop != None:
					tag = self._stack.pop(pop)
					if not self._stack:
						self._tags.append(tag)
	
	#-------------------------------------------	

	def handle_starttag(self, tag, attrs):
		tag = tag.capitalize()
		try:
			tag_clss = getattr(html_tags, tag)
		except:
			tag_clss = html_tags.new_tag(tag)
		tag_inst = tag_clss(**dict(attrs))
		self.push(tag_inst)
		
	
	def handle_startendtag(self, tag, attrs):
		tag = tag.capitalize()
		try:
			tag_clss = getattr(html_tags, tag)
		except:
			tag_clss = html_tags.new_tag(tag)
		tag_inst = tag_clss(**dict(attrs))
		self.push(tag_inst)
		
		if tag_inst.has_endtag:
			self.pop(tag)
		
		
	
	def handle_endtag(self, 	tag):
		self.pop(tag)
		
	
	def handle_data(self, data):
		self.push(html_tags.Text(data))
	
	
	def handle_charref(self, name):
		self.push(html_tags.Raw('&#%s;' % name))

	
	def handle_entityref(self, name):
		self.push(html_tags.Raw('&%s;' % name))
	
	
	def handle_comment(self, data):
		self.push(html_tags.Comment(data))
		
	
	def handle_decl(self, decl):
		decl_ = decl.split(None, 1)
		if len(decl_) == 2:
			if decl_[0].lower() == 'doctype':
				return self.push(html_tags.Doctype(doctype=decl_[1]))
		self.push(html_tags.SgmlDecl(decl))
		
	
	def handle_pi(self, data):
		pi_ = data.split(None, 1)
		if len(pi_) == 2:
			if pi_[0].lower() == 'php':
				return self.push(html_tags.Php(pi_[1]))
		self.push(html_tags.ProcessingInstruction(data))
		
	
