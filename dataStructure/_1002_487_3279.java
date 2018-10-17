import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Scanner;

public class _1002_487_3279 {
	static Scanner sc;
//	static TreeMap<String, Integer> map = new TreeMap<>(); //1.8以上才支持自动类型推导
	static HashMap<String, Integer> map = new HashMap<String,Integer>();
	static char[] d = new char[128];
	
	static
	{
		try {
			sc = new Scanner(new File("./dataStructure/in.txt"));
		}catch(FileNotFoundException e){ sc = new Scanner(System.in); }
		
		d['A']=d['B'] = d['C'] = '2';
	    d['D']=d['E'] = d['F'] = '3';
	    d['G']=d['H'] = d['I'] = '4';
	    d['J']=d['K'] = d['L'] = '5';
	    d['M']=d['N'] = d['O'] = '6';
	    d['P']=d['R'] = d['S'] = '7';
	    d['T']=d['U'] = d['V'] = '8';
	    d['W']=d['X'] = d['Y'] = '9';
	    d['0'] = '0';
	    d['1'] = '1';
	    d['2'] = '2';
	    d['3'] = '3';
	    d['4'] = '4';
	    d['5'] = '5';
	    d['6'] = '6';
	    d['7'] = '7';
	    d['8'] = '8';
	    d['9'] = '9';
	}
	
	
	public static void main(String[] args) throws FileNotFoundException
	{
		
		int n = sc.nextInt();
		for(int i=0; i<n; ++i)
		{
			char[] arr = sc.next().toCharArray();
			StringBuilder sb = new StringBuilder();
			for(int j=0; j<arr.length; ++j) if(arr[j] != '-') sb.append(d[arr[j]]);
			String s = sb.toString();
			if(map.get(s) == null) map.put(s, 1);
			else map.put(s, map.get(s) + 1);
		}
//		boolean noDuplicate = true;
		ArrayList<String> list = new ArrayList<String>();
		for( Entry<String, Integer> e : map.entrySet() )
		{
			if(e.getValue() > 1) 
			{
				String key = e.getKey();
				list.add(key.substring(0, 3) + "-" + key.substring(3) + " " + e.getValue());
//				System.out.println();
//				noDuplicate = false;
			}
		}
		if(list.isEmpty()) System.out.println("No duplicates.");
		else
		{
//			list.sort(String::compareTo);
			java.util.Collections.sort(list);
			for(int i=0,cnt=list.size(); i<cnt; ++i) System.out.println(list.get(i));
		}
		
		sc.close();
	}
}
