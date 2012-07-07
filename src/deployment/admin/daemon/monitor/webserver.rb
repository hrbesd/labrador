#!/usr/bin/ruby

require 'webrick'
include WEBrick
require 'commander'

s = HTTPServer.new( :Port => 9000 )

class MonitorServlet < HTTPServlet::AbstractServlet
  def do_GET(req, res)
    res['Content-Type'] = "text/xml"
    res.body = %{
<?xml version='1.0' encoding='UTF-8'?>
<status>
  <info-values>
  </info-values>
  <info-text>
    <uptime>
      #{ShellWrapper.new.shell_exec('uptime')}
    </uptime>
    <memory>
      #{ShellWrapper.new.shell_exec('free')}
    </memory>
    <cpu>
      #{ShellWrapper.new.shell_exec('w')}
    </cpu>
    <network>
      #{ShellWrapper.new.shell_exec('netstat --protocol=inet | grep 80')}
    </network>
  </info-text>
</status>
}
  end
end

s.mount("/monitor", MonitorServlet)
trap("INT") { s.shutdown } 
s.start

# http://www.thegeekstuff.com/2011/03/sar-examples/