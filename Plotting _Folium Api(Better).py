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
  
#latitude_list = [ 30.3358376, 30.307977, 30.3216419 ]
#longitude_list = [ 77.8701919, 78.048457, 78.0413095 ]


#latlon = [ (51.249443914705175, -0.13878830247011467), (51.249443914705175, -0.13878830247011467), (51.249768239976866, -2.8610415615063034)]
mapit = folium.Map( location=[latitude_list[int(len(latitude_list)/2)], longitude_list[int(len(longitude_list)/2)]], zoom_start=6 )
i=0
while i<len(latitude_list):
    folium.Marker( location=[ latitude_list[i], longitude_list[i] ], fill_color='#43d9de', radius=8 ).add_to( mapit )
    i=i+1

folium.PolyLine(list(zip(latitude_list,longitude_list)), color="red", weight=2.5, opacity=1).add_to(mapit)
#for coord in latitude_list:
  #  folium.Marker( location=[ latitude_list[], longitude_list[0] ], fill_color='#43d9de', radius=8 ).add_to( mapit )

mapit.save( 'map.html')