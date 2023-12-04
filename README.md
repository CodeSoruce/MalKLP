# MalKLP
## Compile & Run

The source code of our paper are in the folder "src".

The source code of each algorithm has four parameters, corresponding to the dataset name (e.g., **D1**) and the three positive integers $k$, $l$ and $\theta$.

* Running example for Algorithms **VFree** and **VFree-**

  Take **VFree** as an example, on dataset **D5** with parameters $\tau_U$ = **5**, $\tau_V$ = **4** and &lambda; = **3**

  > g++ -std=c++11 RecurrenceGroup.cpp -O3 -o VFree
  >
  > ./VFree VFree D5 5 4 3


* Running example for Algorithms **FilterV**, **FilterV-**, **FilterV-FR**, **FilterV-VM** and **BK-ALG+**

  Take **FilterV** as an example, on dataset **D5** with parameters $\tau_U$ = **5**, $\tau_V$ = **4** and &lambda; = **3**

  > g++ -std=c++11 main.cpp graph.cpp -O3 -o FilterV
  >
  > ./FilterV FilterV D5 5 4 3


## Datasets

We provide five datasets in the folder "sample_dataset" for testing, D2 to D6.

Since the download of the clinical database (i.e., D1) requires some private information, we provide its official link here: 
https://physionet.org/content/mimiciii/1.4

Considering the space limitations of GitHub, the remaining datasets can be found at: 
https://1drv.ms/u/s!Aut6uXLH_Qy_bEUkKlJKmCLKnTs
