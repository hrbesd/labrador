require 'shell/system-command'
require 'shell'

class ShellWrapper

  def shell_exec(command, *args)
    random_suffix = "-" + rand(100000).to_s
    out_name = "/tmp/monitor_out_"+random_suffix
    out = File.open(out_name, "w+")
    process = Shell::SystemCommand.new(Shell.new, command, *args)
    while process.active? do end 
    process > out
    out.close
    outtext = IO.read(out_name)
    File.delete(out_name)
    outtext
  end
    
end