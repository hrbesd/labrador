ruby server2.rb &
bash tts_worker.sh &
ruby webserver.rb &
echo "Use 'ruby client.rb' to call this web service."
echo "Use 'wget http://<hostname>:2000/<md5hash>.m4a' to get generated audio."
