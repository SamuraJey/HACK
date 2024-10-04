import java.util.Scanner;

public class IfcCodeConverter {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите код IFC (22 символа): ");
        String ifcCode = scanner.nextLine();

        if (ifcCode.length() != 22) {
            System.out.println("Некорректная длина кода IFC.");
            return;
        }


        StringBuilder binaryString = new StringBuilder();
        for (char c : ifcCode.toCharArray()) {
            if (Character.isUpperCase(c)) {
                binaryString.append('1');
            } else {
                binaryString.append('0');
            }
        }

        while (binaryString.length() < 32) {
            binaryString.insert(0, '0');
        }
