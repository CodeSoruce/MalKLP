# MalKLP
## Compile & Run

The source code of our paper are in the folder "src".

The source code of each algorithm has four parameters, corresponding to the dataset name (e.g., **D1**) and the three positive integers $k$, $l$ and $\theta$.

* Compile

  > g++ -std=c++11 main.cpp graph.cpp -O3 -o main


* Run
  
  > ./main D1 2 4 8


## Datasets

We provide five datasets in the folder "sample_dataset" for testing, D2 to D6.

Since the download of the clinical database (i.e., D1) requires some private information, we provide its official link here: 
https://physionet.org/content/mimiciii/1.4

Considering the space limitations of GitHub, the remaining datasets can be found at: 
https://1drv.ms/u/s!Aut6uXLH_Qy_bEUkKlJKmCLKnTs
