package main

import (
	"bufio"
	"fmt"
	"os"
	"os/exec"
	"strconv"
	"strings"
	"time"
)

func FileExists(path string) bool {
	_, err := os.Stat(path)
	return !os.IsNotExist(err)
}

func ReverseString(input string) string {
	// Reverse the string
	var result string
	for _, v := range input {
		result = string(v) + result
	}
	return result
}

func ReadFile(path string) string {
	// Read file
	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer file.Close()
	var result string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		result += scanner.Text() + "\n"
	}
	return result
}

func SendString(input string, pid int) int64 {
	start := time.Now()
	cmd := exec.Command("./client", fmt.Sprintf("%d", pid), input)
	err := cmd.Run()
	if err != nil {
		return -1
	} else {
		return time.Since(start).Nanoseconds()
	}
}

func FileSize(path string) int64 {
	// Get file size
	file, err := os.Open(path)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer file.Close()
	stat, err := file.Stat()
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	return stat.Size()
}

func main() {
	var speed []int64
	if !FileExists("client") {
		fmt.Println("[!] Please run tester from the root directory")
		os.Exit(1)
	}
	var pid int
	// Read 2nd arg
	if len(os.Args) < 2 {
		fmt.Println("[!] Please specify a PID")
		os.Exit(1)
	}
	pid, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("[!] PID must be an integer")
		os.Exit(1)
	}

	for _, line := range strings.Split(ReadFile("test/hello.txt"), "\n") {
		speed = append(speed, SendString(line, pid))
	}
	for _, line := range strings.Split(ReadFile("test/bongo_tap.txt"), "\n") {
		speed = append(speed, SendString(line, pid))
	}
	for _, line := range strings.Split(ReadFile("test/rgb.txt"), "\n") {
		speed = append(speed, SendString(line, pid))
	}
	for _, line := range strings.Split(ReadFile("test/rainbow.txt"), "\n") {
		speed = append(speed, SendString(line, pid))
	}
	SendString("\n~ Emojis ~\n", pid)
	for _, line := range strings.Split(ReadFile("test/emoji.txt"), "\n") {
		speed = append(speed, SendString(line, pid))
	}
	for _, line := range strings.Split(ReadFile("test/ping.txt"), "\n") {
		speed = append(speed, SendString(line, pid))
	}
	SendString("\n~ 🕒 Benchmark time ~\n", pid)
	// Average speed
	var avg, sum int64
	for _, v := range speed {
		sum += v
	}
	avg = sum / int64(len(speed))
	SendString(fmt.Sprintf("Total transmission time :\n- %d ns", sum), pid)
	SendString(fmt.Sprintf("- %.4f µs", float64(sum/1000)), pid)
	SendString(fmt.Sprintf("- %.4f ms", float64(sum/1000000)), pid)
	SendString(fmt.Sprintf("- %.4f s", float64(sum/1000000000)), pid)
	SendString(fmt.Sprintf("\nAverage transmission speed :\n- %dns", avg), pid)
	SendString(fmt.Sprintf("- %.4f µs", float64(avg/1000)), pid)
	SendString(fmt.Sprintf("- %.4f ms", float64(avg/1000000)), pid)
	SendString(fmt.Sprintf("- %.4f s", float64(avg/1000000000)), pid)

	// Get size of all txt files
	var size int64
	size += FileSize("test/hello.txt")
	size += FileSize("test/bongo_tap.txt")
	size += FileSize("test/rgb.txt")
	size += FileSize("test/rainbow.txt")
	size += FileSize("test/emoji.txt")
	size += FileSize("test/ping.txt")
	SendString(fmt.Sprintf("\nTotal size of all files :\n- %d bytes", size), pid)
	SendString(fmt.Sprintf("- %.4f KB", float64(size/1000)), pid)
	// Average speed to transmit 1 byte
	SendString(fmt.Sprintf("\nAverage speed to transmit 1 byte :\n- %d ns", avg/size), pid)
	SendString(fmt.Sprintf("- %.4f µs", float64(avg/size/1000)), pid)
	SendString(fmt.Sprintf("- %.4f ms", float64(avg/size/1000000)), pid)
	SendString(fmt.Sprintf("- %.4f s", float64(avg/size/1000000000)), pid)
	SendString("\n~ 🕒 Other stats ~\n", pid)
	SendString("file         time (ms)\tsize (bytes)", pid)
	SendString(fmt.Sprintf("hello.txt      %d          %d", speed[0]/1000000, FileSize("test/hello.txt")), pid)
	SendString(fmt.Sprintf("bongo_tap.txt  %d          %d", speed[1]/1000000, FileSize("test/bongo_tap.txt")), pid)
	SendString(fmt.Sprintf("rgb.txt        %d          %d", speed[2]/1000000, FileSize("test/rgb.txt")), pid)
	SendString(fmt.Sprintf("rainbow.txt    %d          %d", speed[3]/1000000, FileSize("test/rainbow.txt")), pid)
	SendString(fmt.Sprintf("emoji.txt      %d          %d", speed[4]/1000000, FileSize("test/emoji.txt")), pid)
	SendString(fmt.Sprintf("ping.txt       %d          %d", speed[5]/1000000, FileSize("test/ping.txt")), pid)

	SendString("\n~ End ~\n", pid)
	SendString("~> Nuttyb0il -- github.com/Nuttyb0il\n                jallerha@student.42.fr", pid)
}
