package main

import (
        "fmt"
        "net"
        "time"
        "strings"
        "io"
)

// Globals
const PORT = "8080"
var chat_log = make([]string, 10) //holds the entire chat
//var chat_log_count = 0;
var chat_log_changes = uint64(0);

func clog(data string){
        //logs data being sent
        
        if chat_log_changes == 0 {
                //if we overflowed the counter, we should probably clear the old logs
                chat_log = make([]string, 10)
        }

        data = strings.Replace(data, "\n", "", -1) //remove trailing newline
        chat_log = append(chat_log, data)
        fmt.Println(strings.TrimRight(data, "\n"))
        //chat_log_count++
        chat_log_changes++
}

func start_server() {
        // Create a TCP listener on port 8080.
        listener, err := net.Listen("tcp", ":" + PORT)
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

        log_pointer := uint64(0) //chat_log_changes //keep track of how much of the log this client has seen
        go func() {
        //polls the log for changes
                for {
                        if chat_log_changes == 0 {
                                log_pointer = 0
                        } else if log_pointer < chat_log_changes {
                                for _, s := range chat_log[log_pointer:]{
                                        conn.Write([]byte(s + "\n"))//sends the log
                                }
                        }
                        log_pointer = chat_log_changes
                        time.Sleep(100 * time.Millisecond)
                }
        }()
        for {
                // Read data from the connection.
                buf := make([]byte, 1024)
                _, err := conn.Read(buf)
                if err != nil {
                        if err == io.EOF {
                                clog(ip.String() + " | Disconnected.")
                        } else {
                                fmt.Print("[ERROR] ")
                                fmt.Println(err)
                        }
                        return
                }
                time.Sleep(10 * time.Millisecond) //slows down spamming
                clog(ip.String() + " | " + strings.TrimRight(fmt.Sprintf("%s", buf), " ")) //what the client said
        }
}
func main() {
        fmt.Println("Starting server...")
        fmt.Println(time.Now())
        go start_server()
        fmt.Scanf("%s");
        fmt.Println("Closing server...")
}
