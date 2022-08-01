import java.util.*;

class solution {
	public static void main(String[] args) {
		Scanner scanner = new Scanner(System.in);
		int nTests = scanner.nextInt();
        int[] fibo = new int[100001];
        fibo[1] = 1;
        fibo[2] = 1;
        for (int i = 3; i < fibo.length; i++) {
            fibo[i] = (fibo[i - 1] + fibo[i - 2]) % 1000000007;
        }
		for (int i = 0; i < nTests; i++) {
            int x = scanner.nextInt();
			System.out.println(fibo[x]);
		}
	}
}