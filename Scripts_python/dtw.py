#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr  1 12:08:53 2020

@author: sylviegibet
"""

""" iterative version of DTW distance computation between two sequences
    @param s1 - the first sequence
    @param s2 - the second sequence
    return The DTW distance, DTW accumulated cost matrixm and the optimal path warping
    Cet algorithme calcule les distances cumulées en partant de début des séquences s1 et s2 jusqu'à la fin . 
    Il remplit une matrice DTW de distances locales : 
         DTW[i,j] = C[i-1,j-1] + min(DTW[i-1,j-1],DTW[i-1,j],DTW[i,j-1]), 
         i et j étant les indices respectifs sur le parcours des séquences s1 et s2
    C[i-1,j-1] représente le coût entre s1[i] et s2[i] : cela peut être une distance euclidienne (au carré) 
    entre 2 points d'une trajectoire
    Il est possible de visualiser les matrices de coût C et de coût cumulé DTW avec plt.imshow()
"""

import numpy as np
from dtaidistance import dtw
from dtaidistance import dtw_visualisation as dtwvis
import seaborn as sns

def DTW_iterative(s1,s2):
    n = s1.shape[0]
    m = s2.shape[0]
    # initialize Cost matrix
    C = computeCMatrix(s1,s2)
    # initialize DTW matrix
    DTW = np.ones((n+1,m+1)) * np.Inf
    DTW[0,0] = 0
    DTW[1,1] = C[0,0]
    # compute DTW
    for i in range(2,n+1):
        DTW[i,1] = C[i-1,0] + DTW[i-1,1]
    for j in range(2,m+1):
        DTW[1,j] = C[0,j-1] + DTW[1,j-1]
    for i in range(2,n+1):
        for j in range(2,m+1):
            DTW[i,j] = C[i-1,j-1] + min(DTW[i-1,j-1],DTW[i-1,j],DTW[i,j-1])
    
    path = optimalWarpingPath(DTW)
    dtw_distance = DTW[-1,-1]/(len(path))
    
    return dtw_distance, DTW, path

""" optimal warping path given a DTW distance matrix
    @param D - The DTW distance matrix
    @return The optimal warping pathm, a 2Darray of (L,2) shape where L is the number of steps
    On part de la fin et on trace un chemin optimal
"""

def optimalWarpingPath(D):
    path = []
    i, j = np.shape(D)
    i=i-1
    j=j-1
    path.append((i,j))
    while i!=1 and j!=1:
        if i==1:
            path.append((1,j-1))
            j=j-1
        elif j==1:
            path.append((i-1,1))
            i=i-1
        else:
            back_step = [D[i-1,j-1],D[i-1,j],D[i,j-1]]
            arg = np.argmin(back_step)
            if arg==0:
                i = i-1
                j = j-1
            elif arg==1:
                i=i-1
            elif arg==2:
                j=j-1
            path.append((i,j))
    path.append((1,1))
    
    return np.asarray(path)

def computeCMatrix(t1,t2):
    return np.asarray([[ computeEuclidianDistance(t1[i],t2[j]) for j in range(len(t2))]for i in range(len(t1))])

def computeEuclidianDistance(p1,p2):
    sum=0
    for i in range(p1.shape[0]):
      sum+=np.power(p1[i]-p2[i],2)
    return np.sqrt(sum)
    

t1=np.random.randint(10)
t2=np.random.randint(13)

print(dtw_distance(t1,t2))