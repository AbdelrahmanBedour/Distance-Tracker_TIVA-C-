#import folium package

import folium
import csv

latitude_list=[]
longitude_list=[]
with open('coordinates.txt','r') as f:
    reader = csv.reader(f)
    for row in reader:
        latitude_list.append(float(row[0]))
        longitude_list.append(float(row[1]))

#locate center point
mapit = folium.Map( location=[latitude_list[int(len(latitude_list)/2)], longitude_list[int(len(longitude_list)/2)]], zoom_start=6 )
i=0

#plot points
while i<len(latitude_list):
    folium.Marker( location=[ latitude_list[i], longitude_list[i] ], fill_color='#43d9de', radius=8 ).add_to( mapit )
    i=i+1

#plot lines between the points
folium.PolyLine(list(zip(latitude_list,longitude_list)), color="red", weight=2.5, opacity=1).add_to(mapit)

mapit.save( 'map.html')