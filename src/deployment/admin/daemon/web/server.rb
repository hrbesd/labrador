# myapp.rb
require 'sinatra'
require '../common/commander'

def exec_command(cmd)
  shell = ShellWrapper.new
  shell.shell_exec("../../console/lab.sh #{cmd}")
end

get '/' do
  'Hello world!'
end

get '/version' do
  exec_command("version")
end

get '/start' do
  exec_command("start")
end

get '/stop' do
  exec_command("stop")
end

get '/log' do
  exec_command("log")
end

get '/help' do
  exec_command("help")
end