import ROOT as root
import numpy as np
import matplotlib.pyplot as plt

from ROOT import TMath , TF1, TH1F
import scipy.stats as st 

#from ROOT import TMath , TCanvas , TGraph , TH1D

#number = 360

voltage = [ 480]# , 490 , 470]# 103, 102 , 104 ]


#definisco degli array in cui salvare dinamicamente i valori da graficare
means = []
errors = []
hv = []

dataset1 = []
dataset2 = []
dataset3 = []
pied1 = []
pied2 = []
pied3 = []


for number in voltage: #ciclo che permette di aprire tutti i file in sequenza
    #filename = '../../../Data/PMTgem/prova_%s_1000eventi.root'%(str(number))
    filename = 'scanED2000.root'
    print("\nAPERTURA di: " + filename)
    
    fileROOT = root.TFile(filename)#"chargeDataBlu.root") #nome del rootfile
    tree = fileROOT.Get("t1") #nome del datatree

    n = 1024
    nCh = 1
    nDat = n*nCh #numero dati per evento...vengono salvati in riga tutti i canali
    nEvts = tree.GetEntries() #numero di eventi
    
    wave = np.zeros((nEvts,nDat))
    time = np.zeros((nEvts,nDat))
    
    print('...(%d) Caricamento Dati...'%(number))
    i=0
    for dat in tree:
        wave[i] = np.array(dat.wave_array)
        time[i] = np.array(dat.time_array)
        i = i+1    


    plt.plot(wave[3])
    plt.show()
    
    print('...Caricamento Dati Completato!...\n\n')

    waveCh4 = np.zeros((nEvts,n))
    waveCh2 = np.zeros((nEvts,n))

    timeCh4 = np.zeros((nEvts,n))
    timeCh2 = np.zeros((nEvts,n))
    
    print('...(%d) Organizzazione Dati...'%(number))
    
    for i in range(nEvts):
        for j in range(nDat):
            if j < nDat/2:
                waveCh4[i][j] = wave[i][j]
                timeCh4[i][j] = time[i][j]
            elif j >= nDat/2:
                waveCh2[i][j-n] = wave[i][j]
                timeCh2[i][j-n] = time[i][j]

    print('...Organizzazione Completata...\n\n')
    j = 0
    print('...Controllo Eventi Da Scartare...')
    for i in range(nEvts):
        if min(waveCh4[i]) < -110 and waveCh4[i].argmin() < 5: 
            #print(i , waveCh4[i].argmin() , timeCh4[i][waveCh4[i].argmin()])
            j = j+1
    print('...Eventi Scartati da ' + filename + ': ' + str(j) + '/' + str(nEvts) + '\n\n')
    
    print('...(%d) Rimozione Piedistallo...'%(number))

    
    for i in range(nEvts):
        waveCh4[i] = waveCh4[i]-np.mean(waveCh4[i][100:200])
    print("...Piedistallo Rimosso...\n\n")
    
    print('...(%d) Calcolo del Segnale in Corrente e Rimozione degli Eventi Da Scartare...'%(number))
    waveCh4A = np.zeros((nEvts-j,n))
    R = 50 #resistenza in Ohm
    piedistallo = np.zeros((nEvts-j,400))
   
    k=0
    for i in np.arange(1,nEvts):
        #butto gli eventi con il picco strano
        if min(waveCh4[i]) >= -110 or (min(waveCh4[i])< -110  and waveCh4[i].argmin() != 1):
            waveCh4A[k] = waveCh4[i]/R #conversione dati Tensione -> dati Corrente
            piedistallo[k] = waveCh4[i][0:400]/R
            k = k+1
        else: 1 
            #print(min(waveCh4[i]) , waveCh4[i].argmin() , i) #check

    print('...Calcolo & Rimozione Completati...\n\n')
            
    print('...CONTROLLO -> Eventi Eliminati da ' + filename + ' ' + str(nEvts - k) + '\n\n')#check
    
    print('...(%d) Calcolo dell\'Integrale di Carica...'%(number))
    integral = np.zeros(k)
    integralP = np.zeros(k)
    #Eseguo l'Integrale


    file = open("integral.dat",'w')
    for i in range(k):
        integral[i] = sum(-waveCh4A[i])
        integralP[i] = sum(-piedistallo[i])
        file.write(str(integral[i])+"\n")

    file.close()

    
    print('...Calcolo Eseguito...\n\n')

    #c = TCanvas()
    #g = TGraph(x.size, x.astype(np.double),y.astype(np.double))
    #fit = g.Fit("gaus" , "S")
    
    #g.Draw("AP")
   
    #----FIT e GRAFICO ISTOGRAMMA----

    xmin = min(integral)
   
    h1 = TH1F( "h1", "Istogramma di Carica $PMT_{gem}$ a %d V ; Charge [pC] ; Counts "%(number), 3050, -50, 3000 )
    for i in integral:
        h1.Fill(i)
       
    xmax = h1.GetBinCenter(h1.GetMaximumBin())
    
    l = np.linspace(xmin , xmax+3 , len(integral))
    func = TF1("fitF" , "gaus" , xmin , xmax+3)
    func.SetParLimits(1 , xmax-1 , xmax+1) 
    #func.SetParLimits(0 , h1.GetMaximum() , h1.GetMaximum())
    
    h1.Fit("fitF" , "R")
    
    #uso la normale definita in scipy usando i parametri estratti dal fit
    pdf = st.norm.pdf(l , func.GetParameter(1) , func.GetParameter(2)) 

    from rootplot import root2matplotlib as r2m
    
    histo1 = r2m.Hist(h1)
    
    histo1.hist(histtype = 'step' , fill = False) #fa l'istogramma
    #plt.plot(l , pdf*func.GetParameter(0)/max(pdf) , label = 'Fit' , color = 'r') 
    plt.grid()
    plt.xlim((xmin,180))
    plt.legend()
    histo1.show_titles()
   ##plt.xlabel('Charge [pC]')
   ##plt.ylabel('Counts')
   ##plt.title(')
    plt.savefig('histo'+ str(number) + '.png')
    plt.show()

    #----------------------------
        
    
    
#fine analisi
    print('---- Analisi su ' + filename + ' COMPLETATA! ----\n\n')
   # number += 10
    
print('----- ANALISI GENERALE CONCLUSA!!!! ------')
