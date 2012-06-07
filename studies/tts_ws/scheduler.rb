require 'digest/md5'

class Scheduler
  def text2speech(string)
    filename=Digest::MD5.hexdigest(string)
    filename='text/' + filename + '.txt'
    if File.exists?(filename) then
      puts "String '#{string[0..48]}' already submitted."
    elsif
      # puts ">> " + string[0..48]
      File.open(filename, 'w') do |f|
        f.puts string
      end
    end
  end 
end
