import java.math.BigInteger;
import java.util.Random;


public class RabinKarp {
	private String pat;
	private long patHash;
	private int M;
	private long Q;
	private int R = 256;
	private long RM;
	
	public RabinKarp(String pat) {
		this.pat = pat;
		this.M = pat.length();
		RM = 1;
		Q = longRandomPrime();
		
		for (int i = 0; i < M - 1; ++i) {
			RM = (R * RM) % Q;
		}
		patHash = hash(pat, M);
	}
	
	public int search(String txt) {
		int N = txt.length();
		long txtHash = hash(txt, M);
		
		if (patHash == txtHash && check(txt, 0)) {
			return 0;
		}
		
		for (int i = M; i < N; ++i) {
			txtHash = (txtHash + Q - RM * txt.charAt(i - M) % Q) % Q;
			txtHash = (txtHash * R + txt.charAt(i)) % Q;
			if (txtHash == patHash) {
				if (check(txt, i - M + 1)) {
					return i - M + 1;
				}
			}
		}
		
		return N;
	}
	
	public static void main(String[] args) {
		String pat = args[0];
		String txt = args[1];
		
		RabinKarp searchRabinKarp = new RabinKarp(pat);
		int offset = searchRabinKarp.search(txt);
		
		System.out.println("txt:" + txt + " pat:" + pat + " offset:" + offset);
	}
	
	private static long longRandomPrime() {
		BigInteger prime = BigInteger.probablePrime(31, new Random());
		return prime.longValue();
	}
	
	private long hash(String key, int M) {
		long h = 0;
		for (int i = 0; i < M; ++i) {
			h = (h * R + key.charAt(i)) % Q;
		}
		
		return h;
	}
	
	private boolean check(String txt, int i) {
		for (int j = 0; j < M; ++j) {
			if (txt.charAt(i + j) != pat.charAt(j)) {
				return false;
			}
		}
		return true;
	}
}
