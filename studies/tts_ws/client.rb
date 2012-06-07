require 'soap/rpc/driver'
proxy = SOAP::RPC::Driver.new("http://localhost:12321", "http://example.com/tts_service")

proxy.add_method('text2speech', 'string')

proxy.text2speech('hello, world')
proxy.text2speech('为简单架构牺牲功能；为简洁的团队沟通牺牲个人偏好；为简便的设计方案和实施流程牺牲完美主义；为简明的产品线牺牲客户。')