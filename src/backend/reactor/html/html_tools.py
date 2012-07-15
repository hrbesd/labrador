

class iter_anchored(object):
	"""wrapper for re.finditer, enforces matching without slipping chars.
	pythons "re" does not have an anchor for the position of the current match, 
	this iterator emulates it. 
	
	import re
	pat = re.compile('o')
	string = 'oooXXXooo'

	enum = iter_anchored(pat, string)
	for match in enum:
		if match == None:
			chars = string[enum.start() : enum.end()]
			print 'found non-matching chars: %s' % chars 	
		else:
			print match.group()
			
	Use the start() and end() methods to find out about the exact position
	of the missmatch (missmatch only!).
	"""						
	AN_NONE = 0
	AN_NOTANCHORED = 1
	AN_QUIT = 2
	
	def __init__(self, compiled_pattern, string):
		"""constructor
		@param compiled_pattern: re pattern
		@param string: string to match
		"""
		self._enum = compiled_pattern.finditer(string)
		self._pos = [0, 0, len(string)]		
		self._last_match = None
		self._flag =  self.AN_NONE
		

	def __iter__(self): return self
	
	def start(self):
		"""returns start index of the current fail position"""
		if self._flag & self.AN_NOTANCHORED:
			return self._pos[0]
		return 0
					
	def end(self):
		"""returns stop index of the current fail position"""
		if  self._flag & self.AN_NOTANCHORED:
			return self._pos[1]
		return 0
	

	def next(self):
		"""returns the next match object in turn or None""" 
				
		if self._flag & self.AN_QUIT:
			raise StopIteration
		else:
			if  self._flag & self.AN_NOTANCHORED:
				self._flag &= ~self.AN_NOTANCHORED
				self._pos[0] = self._last_match.end()
				return self._last_match 
		try:
			self._last_match = self._enum.next()
			if self._last_match.start() != self._pos[0]:
				self._pos[1] = self._last_match.start()
				self._flag |= self.AN_NOTANCHORED
		except StopIteration:
			# check last available match
			if self._last_match and self._last_match.end() == self._pos[2]:
				raise StopIteration
			self._pos[1] = self._pos[2]
			self._flag |= self.AN_NOTANCHORED | self.AN_QUIT
				
		if self._flag & self.AN_NOTANCHORED:
			return None
		
		self._pos[0] = self._last_match.end()		
		return self._last_match
	


		
