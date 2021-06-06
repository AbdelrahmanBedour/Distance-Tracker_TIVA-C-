# import gmplot package
import gmplot
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
  
gmap3 = gmplot.GoogleMapPlotter(latitude_list[int(len(latitude_list)/2)],longitude_list[int(len(longitude_list)/2)], 13)
  
# scatter method of map object 
# scatter points on the google map
gmap3.scatter( latitude_list, longitude_list, '# FF0000', size = 90, marker = False )
  
# Plot method Draw a line in
# between given coordinates

gmap3.plot(latitude_list, longitude_list,'cornflowerblue', edge_width = 4)

gmap3.apikey = "AIzaSyDeRNMnZ__VnQDiATiuz4kPjF_c9r1kWe8"
#gmap3.apikey = "AIzaSyCVK3o95IbZybALGz3IbB7WTvqxzIvsL48" #mine
gmap3.draw('Gmap.html')