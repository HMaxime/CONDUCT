# -*- coding: utf-8 -*-
"""
Created on Thu Mar 19 10:44:26 2020

@author: MaximeHamon
"""
import csv
from plotly.offline import plot
import plotly.express as px
import os
print (os.getcwd())


x = []
y = []
z=[]

with open('Documents/Cours/S2/INF2212_projet/CONDUCT/Unity/Datas/gestes_dynamiques/curvehighLevel-bd707af8-5ba5-4fcd-ace9-773b422c12ce.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=' ')
    for row in plots:
        x.append(float(row[0].replace(",",".")))
        y.append(float(row[1].replace(",",".")))
        z.append(float(row[2].replace(",",".")))

fig = px.scatter_3d(x=x,y=y,z=z)
plot(fig)

#%%
import plotly.express as px
df = px.data.iris()
print(df)
fig = px.scatter_3d(df, x='sepal_length', y='sepal_width', z='petal_width',
              color='species')
plot(fig)
