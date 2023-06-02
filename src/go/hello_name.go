/*
* go-lang
* asks for the users name then says hi
* run with: go run go.go
*/

package main

import ("fmt") // standard text formatting

func main(){
	// promtp
	fmt.Printf("Enter your name: ")

	// get user input
	var name string
	fmt.Scanln(&name)

	// say hello
	fmt.Printf("Hello %s!\n", name)
}

