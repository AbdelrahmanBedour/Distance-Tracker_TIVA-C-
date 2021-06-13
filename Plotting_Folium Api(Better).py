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
mapit = folium.Map( location=[latitude_list[int(len(latitude_list)/2)], longitude_list[int(len(longitude_list)/2)]], zoom_start=17 )

#plot starting point
folium.Marker( location=[ latitude_list[0], longitude_list[0] ] , clustered_marker=True , popup='Starting Location',icon=folium.Icon(color='green', icon='info-sign')).add_to( mapit )

#plot lines following the coordinates between the start and end points
folium.PolyLine(list(zip(latitude_list,longitude_list)), color='darkblue', weight=3.5, opacity=1).add_to(mapit)

#plot stoping point
folium.Marker( location=[ latitude_list[len(latitude_list)-1], longitude_list[len(latitude_list)-1] ] , clustered_marker=True , popup='Stopping Location',icon=folium.Icon(color='red', icon='info-sign')).add_to( mapit )

mapit.save( 'Fmap.html')