OUTPUT = main
LINK = -lboost_system -lcrypto -lssl -lcpprest -lpthread -lsqlite3
INCLUDE = -I/usr/include/cpprest
DB = maple-credit.db
URL = http://host_auto_ip4:8080

build:
	g++ -std=c++11 *.cpp $(LINK) $(INCLUDE) -o $(OUTPUT)

run:
	./$(OUTPUT) $(DB) $(URL)

clean:
	rm $(OUTPUT) $(DB)

push:
	git pull; \
	git add .; \
	read -p "Commit message: " MSG; \
	git commit -m "$$MSG"; \
	git push origin master;

# export LD_LIBRARY_PATH=/usr/local/lib