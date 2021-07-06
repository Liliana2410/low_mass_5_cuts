import numpy as np
import matplotlib.pyplot as plt

filename = 'significance_bins.txt'
f = open(filename, 'r')
data = []
for row in f:
	data.append([x for x in row.split()])	
	

bkg_mu = []
bkg_e = []
lista = []
x=["0-100", "100-200", "200-300", "300-400", "400-500", "500-600", "600-700", "700-800", "800-900","900-1000", "1000-1100", "1100-2500"]
i=1
#suma bkgs 
while i < len(data[0]):
	bkg_mu.append(float(data[0][i]) + float(data[1][i]))
	bkg_e.append(float(data[6][i]) + float(data[7][i]))
	i += 1
	
for i in range (len(data)):
	if (data[i][0] == 's1' or data[i][0] == 's2' or data[i][0] == 's3'  or data[i][0] == 's4'):
		signal = []
		j = 1
		while j < len(data[0]):
			signal.append(float(data[i][j]))
			j+=1
		sigma = []
		colors = ["white", "white", 'cyan', 'red', 'magenta','blue', "white", "white", 'cyan', 'red', 'magenta','blue']
		nombres=["b1", "b2", r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=300 \ GeV$', r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=250 \ G eV$',r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=200 \ GeV$', r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=150 \  GeV$', "b1", "b2", r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=300 \ GeV$', r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=250 \ GeV$',r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=200 \ GeV$', r'$t \overline{t} \ Z^{\prime} \ m(Z^{\prime})=150 \ GeV$']
		if (i<=5):
			for l in range (len(signal)):
				sigma.append(signal[l]/((signal[l]**2 + bkg_mu[l]**2 + (0.25*bkg_mu[l])**2)**(0.5)))
				
			#plt.subplot(1,2,1)
			#plt.plot(x, sigma, label= nombres[i], marker = '.', markersize = 10, linewidth = 2, color = colors[i])
			#plt.title("Muon channel")
			#plt.legend(loc='best')	
			#plt.grid()
			lista.append(sigma)
		else:
			for l in range (len(signal)):
				sigma.append(signal[l]/((signal[l]**2 + bkg_mu[l]**2 + (0.25*bkg_e[l])**2)**(0.5)))
			#plt.subplot(1,2,2)	
			plt.plot(x, sigma, label= nombres[i], marker = '.', markersize = 10, linewidth = 2, color = colors[i])
			#plt.title("Electron channel")
			plt.legend(loc='best')	
			plt.grid()
			lista.append(sigma)

plt.tight_layout()
plt.xlabel(r' Masses of the $Z^{\prime}$ (GeV)')
plt.ylabel(r'Significance ($S^{\mu}$)')	
plt.grid()
plt.show()
for i in range (len(lista)):
	with open('resultados.txt', 'ab') as r:
		np.savetxt(r,[lista[i]], delimiter=' ')	


############################################### PARTE 2 ##########################################################


filename2 = 'masses_significance.txt'
f2 = open(filename2, 'r')
data2 = []
for row in f2:
	data2.append([x for x in row.split()])		

lista2=[]
x2=np.linspace(1,10,10)
lista3 = []
for i in range (len(data2)):
	signal2 = 0
	bkg1 = 0
	bkg2 = 0
	bkg = 0
	if (data2[i][0] == 's4mu'):
		j = 1
		while j < (len(data2[i])):
			signal2= signal2 + float(data2[i][j])
			bkg1 = bkg1 + float(data2[0][j])
			bkg2 = bkg2 + float(data2[1][j])
			j +=1
		bkg = bkg1 + bkg2
		sigma2 = signal2/((signal2**2 + bkg**2 + (0.25*bkg)**2)**(0.5))
		lista2.append(sigma2)
		#print "s1mu", signal2
		#print "b1mu", bkg
		lista3.append(signal2)
		lista3.append(bkg)
		
	elif (data2[i][0] == 's4e'):
		j = 1
		while j < (len(data2[i])):
			signal2= signal2 + float(data2[i][j])
			bkg1 = bkg1 + float(data2[6][j])
			bkg2 = bkg2 + float(data2[7][j])
			j +=1
		bkg = bkg1 + bkg2
		sigma2 = signal2/((signal2**2 + bkg**2 + (0.25*bkg)**2)**(0.5))
		lista2.append(sigma2)	
		#print "s1e", signal2
		#print "b1e", bkg
		lista3.append(signal2)
		lista3.append(bkg)
				
	elif ( (data2[i][0] == 's2mu') or (data2[i][0] == 's3mu') or (data2[i][0] == 's1mu')):
	
		k = 2
		while k < (len(data2[i])):
			bkg1 = bkg1 + float(data2[0][k])
			bkg2 = bkg2 + float(data2[1][k])
			k +=1
		bkg = bkg1 + bkg2
		l = 1
		while l < (len(data2[i])):
			signal2= float(data2[i][l]) + signal2
			l +=1
					
		sigma2 = signal2/((signal2**2 + bkg**2 + (0.25*bkg)**2)**(0.5))
		lista2.append(sigma2)	
		#print "s_mu", signal2
		#print "b_mu", bkg
		lista3.append(signal2)
		lista3.append(bkg)
		
	elif ( (data2[i][0] == 's2e') or (data2[i][0] == 's3e') or (data2[i][0] == 's1e')):
		k = 2
		while k < (len(data2[i])):
			bkg1 = bkg1 + float(data2[6][k])
			bkg2 = bkg2 + float(data2[7][k])
			k +=1
		bkg = bkg1 + bkg2
		l = 1
		while l < (len(data2[i])):
			signal2= float(data2[i][l]) + signal2
			l +=1
				
		sigma2 = signal2/((signal2**2 + bkg**2 + (0.25*bkg)**2)**(0.5))
		lista2.append(sigma2)
		#print "s_e", signal2
		#print "b_e", bkg
		lista3.append(signal2)
		lista3.append(bkg)		
				
		
sigma_combination = []

k = 0
while k < 4:
	NS= lista3[2*k]+lista3[(2*k)+8]
	NB= lista3[(2*k)+1]+lista3[(2*k)+9]
	temp = NS /( (NS**2 + NB**2 + (0.25*NB)**2)**(0.5) )
	sigma_combination.append(temp)
	#print "NS: ", NS 
	#print "nb: ", NB
	k +=1
	
nombres2 = ["s1mu", "s2mu", "s3mu", "s4mu", "s1e", "s2e", "s3e","s4e"]
nombres3 = ["s1", "s2", "s3", "s4"]

textfile = open("resultados2.txt", "w")
for i in range (len(lista2)):
	textfile.write( str(nombres2[i]) + " " +  str(lista2[i]) + "\n")
textfile.write("Combinados" + "\n")

for j in range (len(nombres3)):
	textfile.write( str(nombres3[j]) + " " +  str(sigma_combination[j]) + "\n")
textfile.close()

#######################################################21/06/21#############################################################

l_300_mu = (lista[0][2] + lista[0][3] + lista[0][4] + lista[0][5])/(np.sqrt(4))
l_250_mu = (lista[1][2] + lista[1][3] + lista[1][4])/(np.sqrt(3))
l_200_mu = (lista[2][2] + lista[2][3] + lista[2][4] + lista[2][5])/(np.sqrt(4))
l_150_mu = lista[3][2]

l_300_e = (lista[4][2] + lista[4][3] + lista[4][4] + lista[4][5])/(np.sqrt(4))
l_250_e = (lista[5][2] + lista[5][3] + lista[5][4])/(np.sqrt(3))
l_200_e = (lista[6][2] + lista[6][3] + lista[6][4])/(np.sqrt(3))
l_150_e = (lista[7][2] + lista[6][3])/(np.sqrt(2))

l_300_c = (lista[0][2] + lista[0][3] + lista[0][4] + lista[0][5] + lista[4][2] + lista[4][3] + lista[4][4] + lista[4][5])/(np.sqrt(8))
l_250_c = (lista[1][2] + lista[1][3] + lista[1][4] + lista[5][2] + lista[5][3] + lista[5][4])/(np.sqrt(6))
l_200_c = (lista[2][2] + lista[2][3] + lista[2][4] + lista[2][5] + lista[6][2] + lista[6][3] + lista[6][4])/(np.sqrt(7))
l_150_c = (lista[3][2] + lista[7][2] + lista[6][3])/(np.sqrt(3))


textfile = open("resultados3.txt", "w")

textfile.write( "300 mu" + " " +  str(l_300_mu) + "\n")
textfile.write( "250 mu" + " " +  str(l_250_mu) + "\n")
textfile.write( "200 mu" + " " +  str(l_200_mu) + "\n")
textfile.write( "150 mu" + " " +  str(l_150_mu) + "\n")
textfile.write(" " + "\n")
textfile.write( "300 e" + " " +  str(l_300_e) + "\n")
textfile.write( "250 e" + " " +  str(l_250_e) + "\n")
textfile.write( "200 e" + " " +  str(l_200_e) + "\n")
textfile.write( "150 e" + " " +  str(l_150_e) + "\n")
textfile.write(" " + "\n")
textfile.write("Combinados" + "\n")
textfile.write( "300" + " " +  str(l_300_c) + " " + str(8) + "\n")
textfile.write( "250" + " " +  str(l_250_c) + " " + str(6) + "\n")
textfile.write( "200" + " " +  str(l_200_c) + " " + str(7) + "\n")
textfile.write( "150" + " " +  str(l_150_c) + " " +  str(3) + "\n")
textfile.write(" " + "\n")
textfile.close()


