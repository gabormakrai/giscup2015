package giscup;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;

public class ConvertTextDataMain {
	
	public static void main(String[] args) throws IOException {
//		new ConvertTextDataMain().runNode("d:\\giscup2015\\sfo_nodes.txt", "d:\\giscup2015\\sfo_nodes_qgis.csv");
		new ConvertTextDataMain().runRoad("d:\\giscup2015\\sfo_roads.txt", "d:\\giscup2015\\sfo_roads_qgis.csv");
	}
	
	private void runNode(String inputNodeTextFile, String outputNodeCsvFile) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(inputNodeTextFile)));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputNodeCsvFile)));
		
		String line = "";
		
		bw.write("id,x,y\n");
		
		while ((line=br.readLine()) != null) {
			String idString = line.substring(0, line.indexOf(":"));
			String cString = line.substring(line.indexOf(">")+1);
			cString = cString.substring(cString.indexOf(">")+1);
			cString = cString.substring(0, cString.indexOf(" "));
			bw.write(idString + "," + cString + "\n");
		}
		
		br.close();
		bw.close();
	}
	
	private void runRoad(String inputRoadTextFile, String outputRoadCsvFile) throws IOException {
		
		BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(inputRoadTextFile)));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(outputRoadCsvFile)));
		
		String line = "";
		
		bw.write("id;linestring\n");
		
		while ((line=br.readLine()) != null) {
			String idString = line.substring(0, line.indexOf(":"));
			String cString = line.substring(line.indexOf(">")+1);
			cString = cString.substring(cString.indexOf(">")+1);
			cString = cString.substring(0, cString.indexOf(" <"));
			String[] coordinates = cString.split("\\ ");
			String c0 = coordinates[0].replace(',', ' ');
			String c1 = coordinates[coordinates.length - 1].replace(',', ' ');
			bw.write(idString + ";LINESTRING(" + c0 + ", " + c1 + ")\n");
		}
		
		br.close();
		bw.close();
	}
	
}
