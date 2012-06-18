
from distutils.core import setup
        
RELEASE = True

TRAC_DOC_SPEC = ("/trac.db/wiki/Python/Modules/html", "/trac.db/wiki/Python/Modules/html/*")
TYPE = 'modules'
TRAC_DOC_SPEC = "Python/Modules/html/+"

#import time
#print time.localtime()
RELEASEDATE = (2006, 9, 20, 20, 52, 15, 2, 263, 1)


NAME = 'html'
VERSION = '0.4.0'
DESCRIPTION = 'a python wrapper for HTML 4.0 tags'
AUTHOR = 'Juergen Urner'
EMAIL = 'jUrner@arcor.de'
URL ='http://home.arcor.de/jurner/python'
#MODULES = ['', ]
PACKAGES = ['html', 'html.colors']
#DATA = {'': 'README', '':'MANIFEST'}

if __name__ == '__main__':
    setup(
    name=NAME,
    version=VERSION,
    author = AUTHOR,
    author_email = EMAIL,
    url=URL,
    description=DESCRIPTION,
    long_description=DESCRIPTION,
    license='MIT licence',
    platforms=['Many', ],
    
    packages=PACKAGES,
    #py_modules=MODULES,
    #package_data = DATA
    )
