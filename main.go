package main

import (
	"fmt"
	"strconv"
	"strings"
)

func ifcToHex(ifcCode string) string {
	if len(ifcCode) != 22 {
		panic("Код IFC должен содержать ровно 22 символа.")
	}

	binaryCode := ""
	binaryCode += strings.Repeat("0", 32-len(binaryCode))

	for _, char := range ifcCode {
		if 'A' <= char && char <= 'Z' {
			binaryCode += "1"
		} else {
			binaryCode += "0"
		}
	}

	hexValue := fmt.Sprintf("%04X", mustParseInt(binaryCode, 2))

	return hexValue
}

func mustParseInt(s string, base int) uint32 {
	value, err := strconv.ParseUint(s, base, 32)
	if err != nil {
		panic(err)
	}
	return uint32(value)
}

func main() {
	var ifcCode string
	fmt.Scan(&ifcCode)
	hexResult := ifcToHex(ifcCode)
	fmt.Printf("Шестнадцатеричное значение: %s\n", hexResult)
}
