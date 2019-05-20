import numpy as np
import matplotlib.pyplot as plt
import ROOT as root

choice = 'Cosmici' #'Cosmici' o 'self'
nVolt = 410

fileROOT = root.TFile('../../Data/PMTgem/'+choice+'PMTgem_'+str(nVolt)+'.root')#nome del rootfile
tree = fileROOT.Get("t1") #nome del datatree

n = 1024
nDat = 4*n #numero dati per evento
nEvts = tree.GetEntries() #numero di eventi

#creo due array vuoti per salvare wave_array e time_array del .root

wave = np.zeros((nEvts,nDat))
time = np.zeros((nEvts,nDat))

i=0
for dat in tree:
    wave[i] = np.array(dat.wave_array)
    time[i] = np.array(dat.time_array)
    i = i+1


waveCh1 = np.zeros((nEvts,n))
waveCh2 = np.zeros((nEvts,n))
waveCh3 = np.zeros((nEvts,n))
waveCh4 = np.zeros((nEvts,n))

timeCh1 = np.zeros((nEvts,n))
timeCh2 = np.zeros((nEvts,n))
timeCh3 = np.zeros((nEvts,n))
timeCh4 = np.zeros((nEvts,n))


print(waveCh1.shape , nDat/4)

for i in range(nEvts):
    for j in range(nDat):
        if j < nDat/4:
            waveCh1[i][j] = wave[i][j]
            timeCh1[i][j] = time[i][j]
        elif j >= nDat/4 and j < nDat/2:
            waveCh2[i][j-n] = wave[i][j]
            timeCh2[i][j-n] = time[i][j]
        elif j >= nDat/2 and j < nDat*3/4:
            waveCh3[i][j-2*n] = wave[i][j]
            timeCh3[i][j-2*n] = time[i][j]
        elif j >= nDat*3/4: 
            waveCh4[i][j-3*n] = wave[i][j]
            timeCh4[i][j-3*n] = time[i][j]


j= 0
for i in range(nEvts):
    if min(waveCh4[i]) < -90 and waveCh4[i].argmin() < 5: 
        print(i , waveCh4[i].argmin() , timeCh4[i][waveCh4[i].argmin()])
        j = j+1
print(j)


waveCh4New = np.zeros((nEvts-j,n))
waveCh1New = np.zeros((nEvts-j,n))
k = 0
for i in np.arange(1,nEvts):
    #butto gli eventi con il picco strano e copio Ch1 e Ch4 in nuovi array
    if min(waveCh4[i]) >= -110 or (min(waveCh4[i])< -110  and waveCh4[i].argmin() != 1):
        waveCh4New[k] = waveCh4[i]
        waveCh1New[k] = waveCh1[i]
        k = k+1
        
segnale = []
trigger = []
if choice == 'Cosmici':
    find = 0
    for i in range(k):
        if min(waveCh4New[i][400:800])<-20:
            segnale.append(waveCh4New[i])
            trigger.append(waveCh1New[i])
            find += 1

    segnale = np.array(segnale)
    trigger = np.array(trigger)

elif choice == 'self':
    find = 0
    for i in range(k):
        if min(waveCh1New[i]) < -100 and waveCh1New[i][waveCh1New[i].argmin()+1] < -100:
            segnale.append(waveCh4New[i])
            trigger.append(waveCh1New[i])
            find += 1

    if find == 0 : print('Nessuna coincidenza trovata...')
    else: 
        segnale = np.array(segnale)
        trigger = np.array(trigger)
print('Ci sono %d coincidenze rilevate'%(find))


            

for i in range(len(segnale)):
    plt.title('Waveform no.%d w trigger on %s'%(i,choice))
    plt.xlabel('Time [ns] scale: (400,800) ns')
    plt.ylabel('Voltage [mV] scale: (-110,5) mV')
    plt.ylim((-110,5))
    plt.xlim((400,800))

    plt.plot(trigger[i] , label = 'Coincidence')
    plt.plot(segnale[i] , label = 'Signal')

    plt.legend()
    plt.grid()
    plt.show()
    if raw_input('INVIO -> proseguire\nQUALSIASI+INVIO -> chiudere\n') != '' : break 

