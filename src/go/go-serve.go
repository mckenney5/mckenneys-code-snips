package main

import (
	"fmt"
	"io"
	"io/ioutil"
	"net"
	"strings"
	"time"
)

// Globals
const PORT = "8080"
const LOGGING = true
const BUFFER_SIZE = 5000

var chat_log = make([]string, 10) //holds the entire chat
//var chat_log_count = 0;
var chat_log_changes = uint64(0)

func clog(data string) {
	//logs data being sent

	if chat_log_changes == 0 {
		//if we overflowed the counter, we should probably clear the old logs
		chat_log = make([]string, 10)
	}

	data = strings.Replace(data, "\n", "", -1) //remove trailing newline
	chat_log = append(chat_log, data)
	if LOGGING {
		fmt.Println(strings.TrimRight(data, "\n"))
	}
	chat_log_changes++
}

func start_server() {
	// Create a TCP listener on port 8080.
	listener, err := net.Listen("tcp", ":"+PORT)
	fmt.Println("Listening on port ", PORT)
	if err != nil {
		fmt.Print("[FATAL] ")
		fmt.Println(err)
		return
	}

	// Accept connections on the listener.
	for {
		conn, err := listener.Accept()
		if err != nil {
			fmt.Print("[FATAL] ")
			fmt.Println(err)
			return
		}

		// Handle the connection.
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn) {
	// Get the IP address of the client.
	ip := conn.RemoteAddr().(*net.TCPAddr).IP

	// Print the IP address.
	clog(ip.String() + " | Connected.")

	for {
		// Read data from the connection.
		buf := make([]byte, BUFFER_SIZE)
		n, err := conn.Read(buf)
		if err != nil {
			if err == io.EOF {
				clog(ip.String() + " | Disconnected.")
			} else {
				fmt.Print("[ERROR] ")
				fmt.Println(err)
			}
			return
		}
		data := buf[:n]
		time.Sleep(10 * time.Millisecond)                                          //slows down spamming
		clog(ip.String() + " | " + strings.TrimRight(string(data), " ")) //what the client said
		
		close_connection, server_message := handleHTTP(string(data))
		conn.Write([]byte(server_message))
		if close_connection {
			conn.Close()
			break
		}
	}
}

func getFile(file_name string) (bool, string) {
	if file_name == "/" {
		file_name = "index.html"
	}
	data, err:= ioutil.ReadFile(file_name)
	if err != nil {
		if file_name == "index.html" {
			return true, pageTEST
		}
		fmt.Println(err)
		return false, page500
	}
	return true, string(data) //TODO shoudl handle binary files too
}

func handleHTTP(data string) (bool, string) {
	reply := HTTP_OK
	date := time.Now().Format(time.RFC3339)	
	content := "text/html; charset=UTF-8" //TODO check content type with get request
	accept_range := "Accept-Ranges: bytes"
	connection := "Connection: close" //TODO check for value of CLOSE
	html_file := "<html><h1>Test 1 2 3 4 </h1></html>";
	//--

	token := strings.Split(data, " ")
	t := token[0]
	file_found := false

	if t == "GET" {
		//look for file and retrieve it
		file_found, html_file = getFile(token[1])
		if !file_found {
			reply = HTTP_404
			html_file = page404
		}
	} else if t == "HEAD" {
		//do a get request, but only send the file
		file_found, _ = getFile(token[1])
		if !file_found {
			reply = HTTP_404
		}
		html_file = ""
	} else if t == "POST" || t == "PUT" || t == "DELETE" || t == "CONNECT" || t == "OPTIONS" || t == "TRACE" || t == "PATCH" {
		//not implemented
		html_file = page501

	} else {
		//bad request
		html_file = page500
	}

	full_message := fmt.Sprintf("%s\r\nDate: %s\r\nContent-Type: %s\r\nServer: %s\r\n%s\r\n%s\r\n\r\n%s\r\n\r\n",
			reply, date, content, SERVER_NAME, accept_range, connection, html_file)
	return 	CLOSE, full_message
}

func main() {
	fmt.Println("Starting server...")
	fmt.Println(time.Now())
	go start_server()
	fmt.Scanf("%s")
	fmt.Println("Closing server...")
}


// Built in HTML and Settings
const HTTP_VERSION = "HTTP/1.0"
const SERVER_NAME = "Test Server 0.0.1"
const CLOSE = true //closes the connection after sending
const HTTP_OK = "200 OK"
const HTTP_200 = HTTP_OK
const HTTP_404 = "404 Not Found"
const HTTP_500 = "500 Internal Server Error"
const HTTP_501 = "501 Not Implemented"

const pageTEST = `
<html><head><h1> Testing Page </h1></head>
<body>This is a test page</body>
</html>`

const page404 = `
<html><head><title>404 Not Found<\title>
<h1>404 Page Not Found</h1></head>
<body>The page you requested does not exist</body>
</html>`

const page501 = `
<html><head><title>501 Not Implemented</title>
<h1>501 Not Implemented</h1></head>
<body>The feature you requested is not implemented on this server</body>
</html>`

const page500 = `
<html><head><title>500 Internal Error</title>
<h1>500 Internal Error</h1></head>
<body><p>The server has thrown an error. This could be because:</p>
<p><ul>
<li>You sent an unknown or malformed request</li>
<li>You tried to do something you were not supposed to</li>
<li>Something is broken on our end</li>
</ul></p>
</body>
</html>`

