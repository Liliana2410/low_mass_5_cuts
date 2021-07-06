#include <iostream>
#include <vector>
#include <string>
#include <TH1F.h>
using namespace std;

void plots()
{
   vector<std::string> names_files {"bkg1.root", "bkg2.root","signal2.root", "signal3.root", "signal4.root", "signal5.root"} ;

    vector<std::string> names {"t#bar{t} h> #tau+ #tau-", "t#bar{t}b#bar{b}/h", "t#bar{t}Z' m(Z')= 300 GeV","t#bar{t}Z' m(Z')= 250 GeV", "t#bar{t}Z' m(Z')= 200 GeV", "t#bar{t}Z' m(Z')= 150 GeV"};
    
    vector<std::string> plots {"Efficiencies_e", "StMet_e", "PT_Scalar_leptons_e", "PT_Vector_leptons_e", "dETA_leptons_e", "ETA_lepton1_e", "ETA_lepton2_e", "dPHI_leptons_e", "PHI_lepton1_e", "PHI_lepton2_e", "dPT_Scalar_leptons_e", "dPT_Vector_leptons_e", "Efficiencies_mu", "StMet_mu", "PT_Scalar_leptons_mu", "PT_Vector_leptons_mu", "dETA_leptons_mu", "ETA_lepton1_mu", "ETA_lepton2_mu", "dPHI_leptons_mu", "PHI_lepton1_mu", "PHI_lepton2_mu", "dPT_Scalar_leptons_mu", "dPT_Vector_leptons_mu", "M_leptons_e", "M_leptons_mu"};

    vector<std::string> plots_names {"Number of event after cuts for e #nu_{e}", "Total scalar PT of final states for e #nu_{e}", "Scalar PT of #tau+ #tau- for e #nu_{e}", "PT of #tau+ #tau- for e #nu_{e}", "#delta #eta of #tau+ #tau- for e #nu_{e}", "#eta of #tau_{1} for e #nu_{e}", "#eta of #tau_{2} for e #nu_{e}", "#delta #phi of #tau+ #tau- for e #nu_{e}", "#phi of #tau_{1} for e #nu_{e}", "#phi of #tau_{2} for e #nu_{e}", "Scalar #delta #p_{T} of #tau+ #tau- for e #nu_{e}", "Vector #delta #p_{T} of #tau+ #tau- for e #nu_{e}", "Number of event after cuts for #mu #nu_{#mu}", "Total scalar PT of final states for #mu #nu_{#mu}", "Scalar PT of #tau+ #tau- for #mu #nu_{#mu}", "PT of #tau+ #tau- for #mu #nu_{#mu}", "#delta #eta of #tau+ #tau- for #mu #nu_{#mu}", "#eta of #tau_{1} for #mu #nu_{#mu}", "#eta of #tau_{2} for #mu #nu_{#mu}", "#delta #phi of #tau+ #tau- for #mu #nu_{#mu}", "#phi of #tau_{1} for #mu #nu_{#mu}", "#phi of #tau_{2} for #mu #nu_{#mu}", "Scalar #delta #p_{T} of #tau+ #tau- for #mu #nu_{#mu}", "Vector #delta #p_{T} of #tau+ #tau- for #mu #nu_{#mu}", "Recostructed mass of #tau+ #tau- for #e #nu_{#e}", "Recostructed mass of #tau+ #tau- for #mu #nu_{#mu}"};
   

    vector<std::string> x_labels {"Cuts", "PT  [GeV]", "|P_{T}| (#tau+ #tau-) [GeV]", "P_{T} (#tau+ #tau-) [GeV]", "#delta #eta (#tau+ #tau-) [a.u.]", "#eta (#tau_{1}) [a.u.]", "#eta (#tau_{2}) [a.u.]", "#delta #phi (#tau+ #tau-) [a.u.]", "#phi (#tau_{1}) [a.u.]", "#phi (#tau_{2}) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "Cuts", "PT  [GeV]", "|P_{T}| (#tau+ #tau-) [GeV]", "P_{T} (#tau+ #tau-) [GeV]", "#delta #eta (#tau+ #tau-) [a.u.]", "#eta (#tau_{1}) [a.u.]", "#eta (#tau_{2}) [a.u.]", "#delta #phi (#tau+ #tau-) [a.u.]", "#phi (#tau_{1}) [a.u.]", "#phi (#tau_{2}) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "#delta #p_{T} (#tau+ #tau-) [a.u.]", "M (#tau+ #tau-) [GeV]", "M (#tau+ #tau-) [GeV]"};
    



    vector<int> colors {82, 5, 6, 7, 4, 2, 6, 8};

    vector<int> linestyles {1, 1, 10, 10, 10, 10, 10, 10};
    vector<double> cross {4.3623, 5.2391, 0.13331, 0.16696, 0.28229, 0.33319}; 
    vector<double> total_events_e;
    vector<double> total_events_mu;
    ofstream sig_bin;
    ofstream sig;  
      
    sig_bin.open ("significance_bins.txt");
    sig.open ("masses_significance.txt");
        
    vector<std::string> channel_name {"b1", "b2","s1", "s2", "s3", "s4"};
    for (int j=0; j<names.size(); j++)
    {
    	TFile f(names_files[j].c_str());
    	TH1F *h_mu = (TH1F*)f.Get("Efficiencies_mu");
    	TH1F *h_e = (TH1F*)f.Get("Efficiencies_e");
    	double mu= h_mu->GetBinContent(1);
    	double e= h_e->GetBinContent(1);
	total_events_e.push_back(e);
	total_events_mu.push_back(mu);
    }
    
    TList *l = new TList();
    for(int i=0; i<plots.size(); i++)
    {
        THStack *hs = new THStack("hs", " ");
        TCanvas *c2 = new TCanvas(plots[i].c_str(),"Histos",1280,1024);  
        Double_t x_1,x_2;
        Double_t y_1,y_2;

        x_1 = 0.65;
        x_2 = 0.85;

        y_1 = 0.65;
        y_2 = 0.85;
        auto legend = new TLegend(x_1,y_1,x_2,y_2);
    for (int j=0; j<names.size(); j++)
    {    
        TFile f(names_files[j].c_str());
        TH1F *h = (TH1F*)f.Get(plots[i].c_str());
        h->SetDirectory(0);
        if ((names_files[j] == "signal2.root") ||( names_files[j] == "signal3.root") || (names_files[j] == "signal5.root") ||( names_files[j] == "signal4.root")){
        	h->SetLineColor(colors[j]);
        	h->SetLineStyle(linestyles[j]);
        	h->SetLineWidth(3);
        }
        
        else if ((plots[i]=="M_leptons_mu") || (plots[i]=="M_leptons_e") ){  
        	h->SetFillColor(colors[j]);
        }
        
        else{
        	h->SetLineColor(colors[j]);
        	h->SetLineStyle(linestyles[j]);
        	h->SetLineWidth(3);
        }
       
        
        if ((names_files[j] == "signal2.root") ||( names_files[j] == "signal3.root") || (names_files[j] == "signal5.root") ||( names_files[j] == "signal4.root") ){
        	legend->AddEntry(h,names[j].c_str(),"l");
        }
        
        else if ((plots[i]=="M_leptons_mu") || (plots[i]=="M_leptons_e") ){  
        	legend->AddEntry(h,names[j].c_str(),"f");
        }
        
        else{
        	legend->AddEntry(h,names[j].c_str(),"l");
        }
       
	        if ((plots[i]=="M_leptons_mu")||(plots[i]=="M_leptons_e")){
        	
			Double_t xbins[13] = {0,100,200,300,400,500,600,700,800,900,1000, 1100, 2500};
			TH1F *hnew = (TH1F*)h->Rebin(12,"hnew",xbins);  //creates a new variable bin size histogram hnew
			hnew->SetDirectory(0);			//TH1F *hnew = dynamic_cast<TH1F*>(h->Rebin(10,"hnew",xbins));
			int y=0;
			for (int l=1; l<26; l++){
				if(l<=11) {					
					int x = (h->GetBinContent(2*l)) + (h->GetBinContent((2*l)-1));
					hnew ->SetBinContent (l,x);
				}
					
				else{
					y+= (h->GetBinContent(2*l)) + (h->GetBinContent((2*l)-1));
				}
				
			}
			hnew ->SetBinContent (12,y);
			
			
				
			if (plots[i]=="M_leptons_mu"){
				hnew->Scale(1.0*cross[j]*150/total_events_mu[j]);
				
				sig_bin << channel_name[j] << " " << hnew->GetBinContent(1) << " " << hnew->GetBinContent(2) << " " << hnew->GetBinContent(3) << " " << hnew->GetBinContent(4) << " " << hnew->GetBinContent(5) << " " << hnew->GetBinContent(6) << " " << hnew->GetBinContent(7) << " " << hnew->GetBinContent(8) << " " << hnew->GetBinContent(9) << " " << hnew->GetBinContent(10) << " " << hnew->GetBinContent(11) << " " << hnew->GetBinContent(12)<< "\n";
				
				if ((names_files[j] == "signal5.root") || (names_files[j] == "bkg1.root") || (names_files[j] == "bkg2.root")){
					sig << channel_name[j] <<"mu" << " " << hnew->GetBinContent(2) << " " << hnew->GetBinContent(3) << " " << hnew->GetBinContent(4) << " " << hnew->GetBinContent(5) << " " << hnew->GetBinContent(6) << " " << hnew->GetBinContent(7) << " " << hnew->GetBinContent(8) << " " << hnew->GetBinContent(9) << " " << hnew->GetBinContent(10) << " " << hnew->GetBinContent(11) << " " << hnew->GetBinContent(12) << "\n";
				}	
				else{
					sig << channel_name[j]<<"mu" << " " << hnew->GetBinContent(3) << " " << hnew->GetBinContent(4) << " " << hnew->GetBinContent(5) << " " << hnew->GetBinContent(6) << " " << hnew->GetBinContent(7) << " " << hnew->GetBinContent(8) << " " << hnew->GetBinContent(9) << " " << hnew->GetBinContent(10) << " " << hnew->GetBinContent(11) << " " << hnew->GetBinContent(12) << "\n";
					
				}
				gPad->SetLogy();
		
			}
				
			else if (plots[i]=="M_leptons_e"){
				hnew->Scale(1.0*cross[j]*150/total_events_e[j]);
				
				sig_bin << channel_name[j] << " " << hnew->GetBinContent(1) << " " << hnew->GetBinContent(2) << " " << hnew->GetBinContent(3) << " " << hnew->GetBinContent(4) << " " << hnew->GetBinContent(5) << " " << hnew->GetBinContent(6) << " " << hnew->GetBinContent(7) << " " << hnew->GetBinContent(8) << " " << hnew->GetBinContent(9) << " " << hnew->GetBinContent(10) << " " << hnew->GetBinContent(11) << " " << hnew->GetBinContent(12) << "\n";

				if ((names_files[j] == "signal5.root") || (names_files[j] == "bkg1.root") || (names_files[j] == "bkg2.root")){
					sig << channel_name[j] << "e"<< " " << hnew->GetBinContent(2) << " " << hnew->GetBinContent(3) << " " << hnew->GetBinContent(4) << " " << hnew->GetBinContent(5) << " " << hnew->GetBinContent(6) << " " << hnew->GetBinContent(7) << " " << hnew->GetBinContent(8) << " " << hnew->GetBinContent(9) << " " << hnew->GetBinContent(10) << " " << hnew->GetBinContent(11) << " " << hnew->GetBinContent(12) << "\n";
				}	
				else{
					sig << channel_name[j] << "e"<< " " << hnew->GetBinContent(3) << " " << hnew->GetBinContent(4) << " " << hnew->GetBinContent(5) << " " << hnew->GetBinContent(6) << " " << hnew->GetBinContent(7) << " " << hnew->GetBinContent(8) << " " << hnew->GetBinContent(9) << " " << hnew->GetBinContent(10) << " " << hnew->GetBinContent(11) << " " << hnew->GetBinContent(12) << "\n";
				}
				gPad->SetLogy();
			}
			
			
			legend->SetBorderSize(0);
			hs->Add(hnew); 

        }	
        
        else {
        	h->Scale(1.0/h->Integral());
        	legend->SetBorderSize(0);
        	hs->Add(h); 
        }
    }   
        hs->Draw("NOSTACK HIST");
        hs->GetXaxis()->SetTitle(x_labels[i].c_str());
        if (plots[i]=="M_leptons_mu" || plots[i]=="M_leptons_e" ){
        	hs->GetYaxis()->SetTitle("Num. Events");
        }
        else{ hs->GetYaxis()->SetTitle("a.u."); }
        legend->Draw();
        l->Add(c2);
        std::string filename = plots[i] + "_lowmass.png";
        c2->SaveAs(filename.c_str());
    }
    
    TFile* Output = new TFile("joined.root", "RECREATE"); 
    l->Write();
    Output->Close();
    sig_bin.close();
    sig.close();
    
    
    ofstream myfile_mu;
    ofstream myfile_e;
    ofstream myfile_mu2;
    ofstream myfile_e2;
    
    myfile_mu.open ("events_mu.txt");
    myfile_e.open ("events_e.txt");
    myfile_mu2.open ("efficiencies_mu.txt");
    myfile_e2.open ("efficiencies_e.txt");
    
    
    for (int j=0; j<names.size(); j++)
    {
    	TFile f(names_files[j].c_str());
    	TH1F *h_mu = (TH1F*)f.Get("Efficiencies_mu");
    	TH1F *h_e = (TH1F*)f.Get("Efficiencies_e");
    	
	
	myfile_mu2 << names_files[j] << " &" << 100*h_mu->GetBinContent(2)/h_mu->GetBinContent(1) << " \pm" << 100*h_mu->GetBinContent(2)/h_mu->GetBinContent(1) * sqrt((1/h_mu->GetBinContent(2)) + (1/h_mu->GetBinContent(1)))<< " &" << 100*h_mu->GetBinContent(3)/h_mu->GetBinContent(2) << " \pm" << 100*h_mu->GetBinContent(3)/h_mu->GetBinContent(2) * sqrt((1/h_mu->GetBinContent(3)) + (1/h_mu->GetBinContent(2))) << " &" << 100*h_mu->GetBinContent(4)/h_mu->GetBinContent(3) << " \pm" << 100*h_mu->GetBinContent(4)/h_mu->GetBinContent(3) * sqrt((1/h_mu->GetBinContent(4)) + (1/h_mu->GetBinContent(3))) << " &" << 100*h_mu->GetBinContent(5)/h_mu->GetBinContent(4) << " \pm" << 100*h_mu->GetBinContent(5)/h_mu->GetBinContent(4) * sqrt((1/h_mu->GetBinContent(5)) + (1/h_mu->GetBinContent(4))) << " &" << 100*h_mu->GetBinContent(6)/h_mu->GetBinContent(5) << " \pm" << 100*h_mu->GetBinContent(6)/h_mu->GetBinContent(5) * sqrt((1/h_mu->GetBinContent(6)) + (1/h_mu->GetBinContent(5)))<< " &" << 100*h_mu->GetBinContent(6)/h_mu->GetBinContent(1) << " \pm" << 100*h_mu->GetBinContent(6)/h_mu->GetBinContent(1) * sqrt((1/h_mu->GetBinContent(6)) + (1/h_mu->GetBinContent(1))) << "//" << "\n";
	
	myfile_e2 << names_files[j] << " &" << 100*h_e->GetBinContent(2)/h_e->GetBinContent(1) << " \pm" << 100*h_e->GetBinContent(2)/h_e->GetBinContent(1) * sqrt((1/h_e->GetBinContent(2)) + (1/h_e->GetBinContent(1)))<< " &" << 100*h_e->GetBinContent(3)/h_e->GetBinContent(2) << " \pm" << 100*h_e->GetBinContent(3)/h_e->GetBinContent(2) * sqrt((1/h_e->GetBinContent(3)) + (1/h_e->GetBinContent(2))) << " &" << 100*h_e->GetBinContent(4)/h_e->GetBinContent(3) << " \pm" << 100*h_e->GetBinContent(4)/h_e->GetBinContent(3) * sqrt((1/h_e->GetBinContent(4)) + (1/h_e->GetBinContent(3))) << " &" << 100*h_e->GetBinContent(5)/h_e->GetBinContent(4) << " \pm" << 100*h_e->GetBinContent(5)/h_e->GetBinContent(4) * sqrt((1/h_e->GetBinContent(5)) + (1/h_e->GetBinContent(4))) << " &" << 100*h_e->GetBinContent(6)/h_e->GetBinContent(5) << " \pm" << 100*h_e->GetBinContent(6)/h_e->GetBinContent(5) * sqrt((1/h_e->GetBinContent(6)) + (1/h_e->GetBinContent(5)))<< " &" << 100*h_e->GetBinContent(6)/h_e->GetBinContent(1) << " \pm" << 100*h_e->GetBinContent(6)/h_e->GetBinContent(1) * sqrt((1/h_e->GetBinContent(6)) + (1/h_e->GetBinContent(1))) << "//" << "\n";
	
	h_mu->Scale(1.0*cross[j]*150/total_events_mu[j]);
	h_e->Scale(1.0*cross[j]*150/total_events_e[j]);	
	myfile_mu << names_files[j] << " &" << h_mu->GetBinContent(1) << " &" << h_mu->GetBinContent(2) << " &" << h_mu->GetBinContent(3) << " &" << h_mu->GetBinContent(4) << " &" << h_mu->GetBinContent(5) << " &" << h_mu->GetBinContent(6) << " &" << h_mu->GetBinContent(7) << " &" << h_mu->GetBinContent(8) << "//" << "\n";
	
	myfile_e << names_files[j] << " &" << h_e->GetBinContent(1) << " &" << h_e->GetBinContent(2) << " &" << h_e->GetBinContent(3) << " &" << h_e->GetBinContent(4) << " &" << h_e->GetBinContent(5) << " &" << h_e->GetBinContent(6) << " &" << h_e->GetBinContent(7) << " &" << h_e->GetBinContent(8) << "//" << "\n";
	
    }
    myfile_mu.close();
    myfile_e.close();
    myfile_mu2.close();
    myfile_e2.close();

}



    //PRUEBA *********************************************************
