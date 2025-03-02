import java.util.Scanner;

public class BoothsAlgorithm {
    static int m, r, q, q1, count;
    static int[] M, Q, A;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter multiplicand (M): ");
        m = sc.nextInt();
        System.out.print("Enter multiplier (Q): ");
        r = sc.nextInt();
        sc.close();
        
        boothAlgorithm(m, r);
    }

    static void boothAlgorithm(int m, int r) {
        int n = Integer.toBinaryString(Math.max(Math.abs(m), Math.abs(r))).length();
        count = n + 1; 
        M = toBinaryArray(m, n);
        Q = toBinaryArray(r, n);
        A = new int[n + 1];
        q1 = 0;
        
        System.out.println("Initial values: ");
        printValues();
        
        while (count > 0) {
            int q0 = Q[Q.length - 1];
            if (q0 == 1 && q1 == 0) {
                A = subtract(A, M);
            } else if (q0 == 0 && q1 == 1) {
                A = add(A, M);
            }
            rightShift();
            count--;
            printValues();
        }
        
        System.out.println("Final result: " + getDecimal(A, Q));
    }

    static int[] toBinaryArray(int num, int size) {
        int[] binary = new int[size + 1];
        int temp = Math.abs(num);
        for (int i = size - 1; i >= 0; i--) {
            binary[i] = temp % 2;
            temp /= 2;
        }
        if (num < 0) {
            binary = twosComplement(binary);
        }
        return binary;
    }

    static int[] twosComplement(int[] bin) {
        int carry = 1;
        for (int i = bin.length - 1; i >= 0; i--) {
            bin[i] = bin[i] ^ 1;
            bin[i] += carry;
            if (bin[i] > 1) {
                bin[i] = 0;
            } else {
                carry = 0;
            }
        }
        return bin;
    }

    static int[] add(int[] A, int[] M) {
        int carry = 0;
        for (int i = A.length - 1; i >= 0; i--) {
            int sum = A[i] + M[i] + carry;
            A[i] = sum % 2;
            carry = sum / 2;
        }
        return A;
    }

    static int[] subtract(int[] A, int[] M) {
        return add(A, twosComplement(M));
    }

    static void rightShift() {
        q1 = Q[Q.length - 1];
        int lastA = A[0];
        for (int i = Q.length - 1; i > 0; i--) {
            Q[i] = Q[i - 1];
        }
        Q[0] = A[A.length - 1];
        for (int i = A.length - 1; i > 0; i--) {
            A[i] = A[i - 1];
        }
        A[0] = lastA;
    }

    static int getDecimal(int[] A, int[] Q) {
        int res = 0, factor = 1;
        int[] combined = new int[A.length + Q.length];
        System.arraycopy(A, 0, combined, 0, A.length);
        System.arraycopy(Q, 0, combined, A.length, Q.length);
        boolean isNegative = combined[0] == 1;
        
        if (isNegative) {
            combined = twosComplement(combined);
        }
        
        for (int i = combined.length - 1; i >= 0; i--) {
            res += combined[i] * factor;
            factor *= 2;
        }
        return isNegative ? -res : res;
    }

    static void printValues() {
        System.out.print("A: ");
        for (int bit : A) System.out.print(bit);
        System.out.print(" Q: ");
        for (int bit : Q) System.out.print(bit);
        System.out.println(" Q-1: " + q1);
    }
}
