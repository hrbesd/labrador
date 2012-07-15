
import urllib as _urllib

from html.html_tags import TagBase as _TagBase, html_tidy as _html_tidy
from html.html_constants import ANY, TT_GEN_HTML_FILE
from html.html_parser import Parser as _Parser

__all__ = ['HtmlFile']

#::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

class HtmlFile(_TagBase):
	type = TT_GEN_HTML_FILE
	has_endtag = True
	supported_attrs = []
	can_contain = [ANY, ]
				
	
	def __init__(self, tags=None, string=None, fpath=None, url=None, tidy=False):
		_TagBase.__init__(self)
				
		if tags:
			self.children = tags
		else:
			data = None	
		
			if string:
				data = string
			elif fpath:
				fp = open(fpath)
				try: data = fp.read()
				finally: fp.close()
			elif url:
				fp = _urllib.urlopen(url)
				try: data = fp.read()
				finally: fp.close()
			
			if data:
				if tidy:
					data = _html_tidy(tidy, data)
				p = _Parser()
				self.children = p.feed_string(data)
			
	# prop name
	def _get_name(self):
		return ''
	name = property(_get_name, None, None)
	
	def copy(self):
		return self.__class__(tags=[i.copy() for i in self.children])
		
		
		
			
