hue:
	g++ -std=c++14 -o hue hueProject.C userAccount.C passEncrypt.C hueWidget.C AccountWidget.C -I/usr/local/include -L/usr/local/lib -lwthttp -lwt -lwtdbo -lwtdbosqlite3 -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options

	./hue --docroot . --http-address 0.0.0.0 --http-port 8080
