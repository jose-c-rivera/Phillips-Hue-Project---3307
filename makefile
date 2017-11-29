hue:
	g++ -std=c++14 -o hue hueProject.C SchedulesEdit.C SchedulesWidget.C userAccount.C BridgeEdit.C passEncrypt.C hueWidget.C deleteScheduleWidget.C AccountWidget.C ManageWidget.C LightPage.C  -I/usr/local/include -L/usr/local/lib -lwthttp -lwt -lwtdbo -lwtdbosqlite3 -lboost_system -lboost_thread -lboost_filesystem -lboost_program_options

	./hue --docroot=".;/resources,/css" --http-address 0.0.0.0 --http-port 8080

