require 'soap/rpc/standaloneServer'
require 'scheduler'
NS = 'http://example.com/tts_service'
class Server2 < SOAP::RPC::StandaloneServer
  def on_init
    sched = Scheduler.new
    add_method(sched, 'text2speech', 'string')
  end 
end
svr = Server2.new('Scheduler', NS, '0.0.0.0', 12321) 
trap('INT') { svr.shutdown }
svr.start
