#include "Graph.h"

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Run the code with the following command: ./project4 [input_file] [output_file]" << endl;
        return 1;
    }

    FILE *fp;
    FILE *of;
    fp = fopen(argv[1],"r");
    int width = 0;
    int height = 0;
    int first = 0;
    int next = 0;
    int index = 0;

    int z = fscanf(fp,"%d",&width);
    z = fscanf(fp,"%d",&height);
    z = fscanf(fp,"%d",&first);
    int preceding_line[width];
    Graph g(width*height);
    preceding_line[0] = first;
    for(int i = 1; i < width; i++){
        z = fscanf(fp,"%d",&next);
        preceding_line[i] = next;
        g.addEdge(index,index+1,abs(next-first));
        first = next;
        index++;
    }
    index++;
    for(int j = 1; j < height; j++){
        z = fscanf(fp,"%d",&first);
        g.addEdge(index,index-width,abs(first-preceding_line[0]));
        preceding_line[0] = first;
        for(int k = 1; k < width; k++){
            z = fscanf(fp,"%d",&next);
            g.addEdge(index,index+1,abs(next-first));
            g.addEdge(index-width+1,index+1,abs(next-preceding_line[k]));
            preceding_line[k] = next;
            first = next;
            index++;
        }
        index++;
    }

    int queries = 0;
    z = fscanf(fp,"%d",&queries);

	if(queries == 1){
		const MST& b = g.mst();

		int useless = 0;
    	long int src;
    	long int dst;

    	of = fopen(argv[2],"w");

        z = fscanf(fp,"%d",&first);
        z = fscanf(fp,"%d",&next);
        src = (first-1)*width + (next - 1);
        z = fscanf(fp,"%d",&first);
        z = fscanf(fp,"%d",&next);
        dst = (first-1)*width + (next - 1);
        useless = fprintf(of, "%d\n", b.BFS(src,dst));

        fclose(fp);
    	fclose(of);

        return 0;
    }
    else{
 		Graph b = g.mstbonus();

    	of = fopen(argv[2],"w");
    	int useless = 0;
    	long int src;
    	long int dst;

    	b.rootTree(0);
    	b.precomputeSparseMatrix();

	    for(int i=0; i < queries; i++){
    		z = fscanf(fp,"%d",&first);
    		z = fscanf(fp,"%d",&next);
    		src = (first-1)*width + (next - 1);
    		z = fscanf(fp,"%d",&first);
    		z = fscanf(fp,"%d",&next);
    		dst = (first-1)*width + (next - 1);
    		useless = fprintf(of, "%d\n", b.lca(src,dst));
    	
    	}

    	fclose(fp);
    	fclose(of);
    
    	return 0;	
    }
}