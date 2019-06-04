import ROOT as root
import numpy as np
import matplotlib.pyplot as plt

fileNumber = 490
fileROOT = root.TFile('../../Data/PMTgem/verticaleNew_470.root')
#prova_' + str(fileNumber) + '_1000eventi.root')
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

waveTry = []
timeTry = []

for i in range(nEvts):
    #if min(waveCh4[i]) <= -50:
     waveTry.append(waveCh4[i])#-np.mean(waveCh4[i][100:200])
     timeTry.append(timeCh4[i])

waveTry = np.array(waveTry)
timeTry = np.array(timeTry)

print(len(waveTry))
for i in np.arange(1,len(waveTry)):
    plt.plot(timeTry[i] , waveTry[i])
    plt.grid()
    plt.xlabel('Time [ns]')
    plt.ylabel('Voltage [mV]')
    plt.title('Waveform no.%d con $\Delta V_{GEM}$ = %d V'%(i , fileNumber))
    #plt.xlim(0,3)
    plt.show()
    #premere invio per proseguire, altro per concludere
    if raw_input('INVIO -> proseguire\nQUALSIASI+INVIO -> chiudere\n') != '' : break 
