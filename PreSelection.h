#ifndef PreSelection_h
#define PreSelection_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TString.h>

#include "ubana/myClasses/Constants.h"

#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace Constants;

class PreSelection {

private:
	TString fWhichSample;

public :

   //TTree           *fChain;   //!pointer to the analyzed TTree or TChain
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain

   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   std::vector<double>  *EventWeight;
   std::vector<double>  *T2KEventWeight;
   std::vector<double>  *ROOTinoEventWeight;   

   vector<double>  *All_UBGenie_EventWeight;
   vector<double>  *AxFFCCQEshape_UBGenie_EventWeight;
   vector<double>  *DecayAngMEC_UBGenie_EventWeight;
   vector<double>  *NormCCCOH_UBGenie_EventWeight;
   vector<double>  *NormNCCOH_UBGenie_EventWeight;
//   vector<double>  *RPA_CCQE_Reduced_UBGenie_EventWeight;
   vector<double>  *RPA_CCQE_UBGenie_EventWeight;
   vector<double>  *ThetaDelta2NRad_UBGenie_EventWeight;
   vector<double>  *Theta_Delta2Npi_UBGenie_EventWeight;
   vector<double>  *VecFFCCQEshape_UBGenie_EventWeight;
   vector<double>  *XSecShape_CCMEC_UBGenie_EventWeight;
   vector<double>  *expskin_FluxUnisim_EventWeight;
   vector<double>  *horncurrent_FluxUnisim_EventWeight;
   vector<double>  *kminus_PrimaryHadronNormalization_EventWeight;
   vector<double>  *kplus_PrimaryHadronFeynmanScaling_EventWeight;
   vector<double>  *kzero_PrimaryHadronSanfordWang_EventWeight;
   vector<double>  *nucleoninexsec_FluxUnisim_EventWeight;
   vector<double>  *nucleonqexsec_FluxUnisim_EventWeight;
   vector<double>  *nucleontotxsec_FluxUnisim_EventWeight;
   vector<double>  *piminus_PrimaryHadronSWCentralSplineVariation_EventWeight;
   vector<double>  *pioninexsec_FluxUnisim_EventWeight;
   vector<double>  *pionqexsec_FluxUnisim_EventWeight;
   vector<double>  *piontotxsec_FluxUnisim_EventWeight;
   vector<double>  *piplus_PrimaryHadronSWCentralSplineVariation_EventWeight;
   vector<double>  *reinteractions_piminus_Geant4_EventWeight;
   vector<double>  *reinteractions_piplus_Geant4_EventWeight;
   vector<double>  *reinteractions_proton_Geant4_EventWeight;
   vector<double>  *xsr_scc_Fa3_SCC_EventWeight;
   vector<double>  *xsr_scc_Fv3_SCC_EventWeight;

   Int_t           isData;
   Int_t           RunNumber;
   Int_t           SubRunNumber;
   Int_t           EventNumber;
   Int_t           ientry;
   Int_t           EventPassedSwTrigger;
   Int_t           NumberTracks;
   std::vector<double>  *Track_Length;
   std::vector<double>  *Track_Phi;
   std::vector<double>  *Track_Theta;
   std::vector<double>  *Track_StartX;
   std::vector<double>  *Track_StartY;
   std::vector<double>  *Track_StartZ;
   std::vector<double>  *Track_EndX;
   std::vector<double>  *Track_EndY;
   std::vector<double>  *Track_EndZ;
   std::vector<double>  *Track_Momentum_MCS;
   std::vector<double>  *Track_Momentum_Range_Muon;
   std::vector<double>  *Track_Momentum_Range_Proton;
   std::vector<int>     *Track_IsBeamEvent;
   std::vector<int>     *Track_MCParticle_Mother;
   std::vector<int>     *Track_MCParticle_PdgCode;
   std::vector<double>  *Track_MCParticle_Vx;
   std::vector<double>  *Track_MCParticle_Vy;
   std::vector<double>  *Track_MCParticle_Vz;
   std::vector<double>  *Track_MCParticle_EndX;
   std::vector<double>  *Track_MCParticle_EndY;
   std::vector<double>  *Track_MCParticle_EndZ;
//   std::vector<std::string>  *Track_MCParticle_Process;
   std::vector<double>  *Track_MCParticle_E;
   std::vector<double>  *Track_MCParticle_P;
   std::vector<double>  *Track_MCParticle_Px;
   std::vector<double>  *Track_MCParticle_Py;
   std::vector<double>  *Track_MCParticle_Pz;
   std::vector<double>  *Track_MCParticle_Mass;
   std::vector<double>  *Track_MCParticle_Purity;
   std::vector<int>     *Track_MCParticle_Origin;
/*   std::vector<int>     *Track_AssMCTruth_NParticles;
   std::vector<int>     *Track_AssMCTruth_Nu_PdgCode;
   std::vector<int>     *Track_AssMCTruth_Lepton_PdgCode;
   std::vector<int>     *Track_AssMCTruth_CCNC;
   std::vector<int>     *Track_AssMCTruth_Mode;*/
//   std::vector<int>     *Track_MCParticle_InteractionType;
//   std::vector<int>     *Track_MCParticle_Mode;
/*   std::vector<double>  *Track_AssMCTruth_QSqr;
   std::vector<double>  *Track_AssMCTruth_X;
   std::vector<double>  *Track_AssMCTruth_Y;
   std::vector<double>  *Track_AssMCTruth_W;*/
/*   std::vector<int>     *Track_Calorimetry_Plane2_PlaneID;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_ResidualRange;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_dEdx;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_dQdx;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_TruncdEdx;
   std::vector<std::vector<double> > *Track_Calorimetry_Plane2_TruncdQdx;
   std::vector<double>  *Track_Calorimetry_Plane2_CaliKineticEnergy;
   Int_t           Track_ParticleId_Pdg;
   std::vector<double>  *Track_ParticleId_MinChi2;
   std::vector<double>  *Track_ParticleId_Chi2Proton;
   std::vector<double>  *Track_ParticleId_Chi2Kaon;
   std::vector<double>  *Track_ParticleId_Chi2Pion;
   std::vector<double>  *Track_ParticleId_Chi2Muon;
   std::vector<double>  *Track_ParticleId_PIDA;
   std::vector<double>  *Track_ParticleId_Ndf;
   std::vector<double>  *Track_ParticleId_DeltaChi2;
   std::vector<double>  *Track_ParticleId_MissingE;
   std::vector<double>  *Track_ParticleId_MissingEavg;
   std::vector<double>  *Track_ParticleId_PlaneID;*/
   
/*   std::vector<std::vector<double> > *Track_PlaneID;*/
/*   std::vector<std::vector<double> > *Track_Start_Wire;*/
/*   std::vector<std::vector<double> > *Track_Start_Time;*/
/*   std::vector<std::vector<double> > *Track_End_Wire;*/
/*   std::vector<std::vector<double> > *Track_End_Time;*/

   std::vector<int>     *Track_NumberAssHits;
   std::vector<std::vector<double> > *Track_AssHit_Integral;
   std::vector<std::vector<double> > *Track_AssHit_PeakTime;
   std::vector<std::vector<double> > *Track_AssHit_Wire;
   std::vector<std::vector<int> > *Track_AssHit_WireID_Plane;   

   Int_t           NumberHits;
   vector<double>  *Hit_Integral;
   vector<double>  *Hit_PeakTime;
   vector<double>  *Hit_Wire;
   vector<int>     *Hit_WireID_Plane;
   
   Int_t           NumberFlashesBeam;
   std::vector<double>  *FlashesBeam_Time;
/*   std::vector<double>  *FlashesBeam_Twidth;*/
/*   std::vector<double>  *FlashesBeam_AbsTime;
   std::vector<int>     *FlashesBeam_Frame;*/
   std::vector<double>  *FlashesBeam_Ycenter;
/*   std::vector<double>  *FlashesBeam_Ywidth;*/
   std::vector<double>  *FlashesBeam_Zcenter;
/*   std::vector<double>  *FlashesBeam_Zwidth;*/
   std::vector<double>  *FlashesBeam_TotalPE;
/*   std::vector<std::vector<double> > *FlashesBeam_WireCenters;
   std::vector<std::vector<double> > *FlashesBeam_WireWidths;
   std::vector<double>  *FlashesBeam_FastToTotal;*/
/*   std::vector<double>  *MCParticle_AssMCTruth_QSqr;
   std::vector<double>  *MCParticle_AssMCTruth_X;
   std::vector<double>  *MCParticle_AssMCTruth_Y;
   std::vector<double>  *MCParticle_AssMCTruth_W;*/

   std::vector<double> *Track_ParticleId_MIPScore_ThreePlanePID;
   std::vector<double> *Track_ParticleId_MuonScore_ThreePlanePID;
   std::vector<double> *Track_ParticleId_ProtonScore_ThreePlanePID;
   std::vector<double> *Track_ParticleId_PionScore_ThreePlanePID;

   std::vector<double> *Track_ParticleId_MIPScore_Chi2_YPlane;
   std::vector<double> *Track_ParticleId_MuonScore_Chi2_YPlane;
   std::vector<double> *Track_ParticleId_ProtonScore_Chi2_YPlane;
   std::vector<double> *Track_ParticleId_PionScore_Chi2_YPlane;

   std::vector<double> *Track_ParticleId_MIPScore_Chi2_UPlane;
   std::vector<double> *Track_ParticleId_MuonScore_Chi2_UPlane;
   std::vector<double> *Track_ParticleId_ProtonScore_Chi2_UPlane;
   std::vector<double> *Track_ParticleId_PionScore_Chi2_UPlane;

   std::vector<double> *Track_ParticleId_MIPScore_Chi2_VPlane;
   std::vector<double> *Track_ParticleId_MuonScore_Chi2_VPlane;
   std::vector<double> *Track_ParticleId_ProtonScore_Chi2_VPlane;
   std::vector<double> *Track_ParticleId_PionScore_Chi2_VPlane;

   std::vector<double> *Track_LLR_PID;

   std::vector<int>     *MCTruth_CCNC;
   std::vector<int>     *MCTruth_Mode;
   std::vector<int>     *MCTruth_InteractionType;
   std::vector<double>     *MCTruth_Particle_Nu_E;
   std::vector<double>     *MCTruth_Particle_Nu_Vx;
   std::vector<double>     *MCTruth_Particle_Nu_Vy;
   std::vector<double>     *MCTruth_Particle_Nu_Vz;

   Int_t           NumberNuMuPFParticles;
   vector<int>     *PFParticle_NumberNuMuDaughters;
   vector<vector<int> > *PFParticle_NumberNuMuDaughtersPdgCode;
   vector<vector<double>> *TracksFromCurrentPFParticleStartX;
   vector<vector<double> > *TracksFromCurrentPFParticleTrackScore;

   vector<vector<double> > *VertexFromCurrentPFParticlePositionX;
   vector<vector<double> > *VertexFromCurrentPFParticlePositionY;
   vector<vector<double> > *VertexFromCurrentPFParticlePositionZ;

   vector<vector<double> > *VertexFromCurrentPFParticlePlaneX;
   vector<vector<double> > *VertexFromCurrentPFParticlePlaneY;
   vector<vector<double> > *VertexFromCurrentPFParticlePlaneZ;

   vector<vector<double> > *VertexFromCurrentPFParticleWireX;
   vector<vector<double> > *VertexFromCurrentPFParticleWireY;
   vector<vector<double> > *VertexFromCurrentPFParticleWireZ;

   vector<vector<double> > *VertexFromCurrentPFParticleTimeX;
   vector<vector<double> > *VertexFromCurrentPFParticleTimeY;
   vector<vector<double> > *VertexFromCurrentPFParticleTimeZ;

   std::vector<double>  *MCParticle_Vx;
   std::vector<double>  *MCParticle_Vy;
   std::vector<double>  *MCParticle_Vz;
   std::vector<double>  *MCParticle_EndX;
   std::vector<double>  *MCParticle_EndY;
   std::vector<double>  *MCParticle_EndZ;

   std::vector<int>     *MCParticle_StatusCode;
   std::vector<std::string>  *MCParticle_Process;   
   std::vector<int>     *MCParticle_PdgCode;
   std::vector<double>     *MCParticle_P;

   std::vector<double> *PFParticle_NuScore;
   std::vector<double> *PFParticle_FlashScore;

   // List of branches

   TBranch        *b_EventWeight;   //!
   TBranch        *b_T2KEventWeight;   //!
   TBranch        *b_ROOTinoEventWeight;   //! 

   TBranch        *b_All_UBGenie_EventWeight;   //!              
   TBranch        *b_AxFFCCQEshape_UBGenie_EventWeight;   //!    
   TBranch        *b_DecayAngMEC_UBGenie_EventWeight;   //!      
   TBranch        *b_NormCCCOH_UBGenie_EventWeight;   //!        
   TBranch        *b_NormNCCOH_UBGenie_EventWeight;   //!        
//   TBranch        *b_RPA_CCQE_Reduced_UBGenie_EventWeight;   //! 
   TBranch        *b_RPA_CCQE_UBGenie_EventWeight;   //!         
   TBranch        *b_ThetaDelta2NRad_UBGenie_EventWeight;   //!  
   TBranch        *b_Theta_Delta2Npi_UBGenie_EventWeight;   //!  
   TBranch        *b_VecFFCCQEshape_UBGenie_EventWeight;   //!   
   TBranch        *b_XSecShape_CCMEC_UBGenie_EventWeight;   //!  
   TBranch        *b_expskin_FluxUnisim_EventWeight;   //!       
   TBranch        *b_horncurrent_FluxUnisim_EventWeight;   //!   
   TBranch        *b_kminus_PrimaryHadronNormalization_EventWeight;   //!       
   TBranch        *b_kplus_PrimaryHadronFeynmanScaling_EventWeight;   //!       
   TBranch        *b_kzero_PrimaryHadronSanfordWang_EventWeight;   //!          
   TBranch        *b_nucleoninexsec_FluxUnisim_EventWeight;   //!
   TBranch        *b_nucleonqexsec_FluxUnisim_EventWeight;   //! 
   TBranch        *b_nucleontotxsec_FluxUnisim_EventWeight;   //!
   TBranch        *b_piminus_PrimaryHadronSWCentralSplineVariation_EventWeight;   //!          
   TBranch        *b_pioninexsec_FluxUnisim_EventWeight;   //!   
   TBranch        *b_pionqexsec_FluxUnisim_EventWeight;   //!    
   TBranch        *b_piontotxsec_FluxUnisim_EventWeight;   //!   
   TBranch        *b_piplus_PrimaryHadronSWCentralSplineVariation_EventWeight;   //!           
   TBranch        *b_reinteractions_piminus_Geant4_EventWeight;   //!           
   TBranch        *b_reinteractions_piplus_Geant4_EventWeight;   //!            
   TBranch        *b_reinteractions_proton_Geant4_EventWeight;   //!            
   TBranch        *b_xsr_scc_Fa3_SCC_EventWeight;   //!          
   TBranch        *b_xsr_scc_Fv3_SCC_EventWeight;   //! 

   TBranch        *b_isData;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_SubRunNumber;   //!
   TBranch        *b_EventNumber;   //!
   TBranch        *b_ientry;   //!
   TBranch        *b_EventPassedSwTrigger;   //!
   TBranch        *b_NumberTracks;   //!
   TBranch        *b_Track_Length;   //!
   TBranch        *b_Track_Phi;   //!
   TBranch        *b_Track_Theta;   //!
   TBranch        *b_Track_StartX;   //!
   TBranch        *b_Track_StartY;   //!
   TBranch        *b_Track_StartZ;   //!
   TBranch        *b_Track_EndX;   //!
   TBranch        *b_Track_EndY;   //!
   TBranch        *b_Track_EndZ;   //!
   TBranch        *b_Track_Momentum_MCS;   //!
   TBranch        *b_Track_Momentum_Range_Muon;   //!
   TBranch        *b_Track_Momentum_Range_Proton;   //!
   TBranch        *b_Track_IsBeamEvent;   //!
   TBranch        *b_Track_MCParticle_StatusCode;   //!
   TBranch        *b_Track_MCParticle_Mother;   //!
   TBranch        *b_Track_MCParticle_PdgCode;   //!
   TBranch        *b_Track_MCParticle_Vx;   //!
   TBranch        *b_Track_MCParticle_Vy;   //!
   TBranch        *b_Track_MCParticle_Vz;   //!
   TBranch        *b_Track_MCParticle_EndX;   //!
   TBranch        *b_Track_MCParticle_EndY;   //!
   TBranch        *b_Track_MCParticle_EndZ;   //!
//   TBranch        *b_Track_MCParticle_Process;   //!
   TBranch        *b_Track_MCParticle_E;   //!
   TBranch        *b_Track_MCParticle_P;   //!
   TBranch        *b_Track_MCParticle_Px;   //!
   TBranch        *b_Track_MCParticle_Py;   //!
   TBranch        *b_Track_MCParticle_Pz;   //!
   TBranch        *b_Track_MCParticle_Mass;   //!
   TBranch        *b_Track_MCParticle_Purity;   //!
   TBranch        *b_Track_MCParticle_Origin;   //!
/*   TBranch        *b_Track_AssMCTruth_NParticles;   //!
   TBranch        *b_Track_AssMCTruth_Nu_PdgCode;   //!
   TBranch        *b_Track_AssMCTruth_Lepton_PdgCode;   //!
   TBranch        *b_Track_AssMCTruth_CCNC;   //!
   TBranch        *b_Track_AssMCTruth_Mode;*/   //!
//   TBranch        *b_Track_MCParticle_InteractionType;   //!
//   TBranch        *b_Track_MCParticle_Mode;   //!
/*   TBranch        *b_Track_AssMCTruth_QSqr;   //!
   TBranch        *b_Track_AssMCTruth_X;   //!
   TBranch        *b_Track_AssMCTruth_Y;   //!
   TBranch        *b_Track_AssMCTruth_W;*/   //!
/*   TBranch        *b_Track_Calorimetry_Plane2_PlaneID;   //!
   TBranch        *b_Track_Calorimetry_Plane2_ResidualRange;   //!
   TBranch        *b_Track_Calorimetry_Plane2_dEdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_dQdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_TruncdEdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_TruncdQdx;   //!
   TBranch        *b_Track_Calorimetry_Plane2_CaliKineticEnergy;   //!
   TBranch        *b_Track_ParticleId_Pdg;   //!
   TBranch        *b_Track_ParticleId_MinChi2;   //!
   TBranch        *b_Track_ParticleId_Chi2Proton;   //!
   TBranch        *b_Track_ParticleId_Chi2Kaon;   //!
   TBranch        *b_Track_ParticleId_Chi2Pion;   //!
   TBranch        *b_Track_ParticleId_Chi2Muon;   //!
   TBranch        *b_Track_ParticleId_PIDA;   //!
   TBranch        *b_Track_ParticleId_Ndf;   //!
   TBranch        *b_Track_ParticleId_DeltaChi2;   //!
   TBranch        *b_Track_ParticleId_MissingE;   //!
   TBranch        *b_Track_ParticleId_MissingEavg;   //!
   TBranch        *b_Track_ParticleId_PlaneID;   //!*/

/*   TBranch        *b_Track_PlaneID;   //!      */
/*   TBranch        *b_Track_Start_Wire;   //!*/
/*   TBranch        *b_Track_Start_Time;   //!*/
/*   TBranch        *b_Track_End_Wire;   //!*/
/*   TBranch        *b_Track_End_Time;   //!*/

   TBranch        *b_Track_NumberAssHits;   //!
   TBranch        *b_Track_AssHit_Integral;   //!
   TBranch        *b_Track_AssHit_PeakTime;   //!
   TBranch        *b_Track_AssHit_Wire;   //!
   TBranch        *b_Track_AssHit_WireID_Plane;   //!

   TBranch        *b_NumberHits;   //!                                                                                                                                                                
   TBranch        *b_Hit_Integral;   //!                                                                                                                                                              
   TBranch        *b_Hit_PeakTime;   //!                                                                                                                                                               
   TBranch        *b_Hit_Wire;   //!                                                                                                                                                                   
   TBranch        *b_Hit_WireID_Plane;   //! 
   
   TBranch        *b_NumberFlashesBeam;   //!
   TBranch        *b_FlashesBeam_Time;   //!
/*   TBranch        *b_FlashesBeam_Twidth;   //!*/
/*   TBranch        *b_FlashesBeam_AbsTime;   //!
   TBranch        *b_FlashesBeam_Frame;*/   //!
   TBranch        *b_FlashesBeam_Ycenter;   //!
/*   TBranch        *b_FlashesBeam_Ywidth;   //!*/
   TBranch        *b_FlashesBeam_Zcenter;   //!
/*   TBranch        *b_FlashesBeam_Zwidth;   //!*/
   TBranch        *b_FlashesBeam_TotalPE;   //!
/*   TBranch        *b_FlashesBeam_WireCenters;   //!
   TBranch        *b_FlashesBeam_WireWidths;   //!
   TBranch        *b_FlashesBeam_FastToTotal;*/   //!
/*   TBranch        *b_MCParticle_AssMCTruth_QSqr;   //!
   TBranch        *b_MCParticle_AssMCTruth_X;   //!
   TBranch        *b_MCParticle_AssMCTruth_Y;   //!
   TBranch        *b_MCParticle_AssMCTruth_W;*/   //!

//   TBranch        *b_Track_ParticleId_MIPScore_ThreePlanePID;
//   TBranch        *b_Track_ParticleId_MuonScore_ThreePlanePID;
   TBranch        *b_Track_ParticleId_ProtonScore_ThreePlanePID;
//   TBranch        *b_Track_ParticleId_PionScore_ThreePlanePID;

//   TBranch        *b_Track_ParticleId_MIPScore_Chi2_YPlane;
//   TBranch        *b_Track_ParticleId_MuonScore_Chi2_YPlane;
   TBranch        *b_Track_ParticleId_ProtonScore_Chi2_YPlane;
//   TBranch        *b_Track_ParticleId_PionScore_Chi2_YPlane;

//   TBranch        *b_Track_ParticleId_MIPScore_Chi2_UPlane;
//   TBranch        *b_Track_ParticleId_MuonScore_Chi2_UPlane;
   TBranch        *b_Track_ParticleId_ProtonScore_Chi2_UPlane;
//   TBranch        *b_Track_ParticleId_PionScore_Chi2_UPlane;

//   TBranch        *b_Track_ParticleId_MIPScore_Chi2_VPlane;
//   TBranch        *b_Track_ParticleId_MuonScore_Chi2_VPlane;
   TBranch        *b_Track_ParticleId_ProtonScore_Chi2_VPlane;
//   TBranch        *b_Track_ParticleId_PionScore_Chi2_VPlane;

   TBranch        *b_Track_LLR_PID;

   TBranch        *b_MCTruth_CCNC;   //!
   TBranch        *b_MCTruth_Mode;   //!
   TBranch        *b_MCTruth_InteractionType;   //!
   TBranch        *b_MCTruth_Particle_Nu_E;   //!
   TBranch        *b_MCTruth_Particle_Nu_Vx;   //!
   TBranch        *b_MCTruth_Particle_Nu_Vy;   //!
   TBranch        *b_MCTruth_Particle_Nu_Vz;   //!

   TBranch        *b_NumberNuMuPFParticles;   //!
   TBranch        *b_PFParticle_NumberNuMuDaughters;   //!
   TBranch        *b_PFParticle_NumberNuMuDaughtersPdgCode;   //!
   TBranch        *b_TracksFromCurrentPFParticleStartX;   //!
   TBranch        *b_TracksFromCurrentPFParticleTrackScore;   //!

   TBranch        *b_VertexFromCurrentPFParticlePositionX;   //!
   TBranch        *b_VertexFromCurrentPFParticlePositionY;   //!
   TBranch        *b_VertexFromCurrentPFParticlePositionZ;   //!

   TBranch        *b_VertexFromCurrentPFParticlePlaneX;   //!
   TBranch        *b_VertexFromCurrentPFParticlePlaneY;   //!
   TBranch        *b_VertexFromCurrentPFParticlePlaneZ;   //!

   TBranch        *b_VertexFromCurrentPFParticleWireX;   //!
   TBranch        *b_VertexFromCurrentPFParticleWireY;   //!
   TBranch        *b_VertexFromCurrentPFParticleWireZ;   //!

   TBranch        *b_VertexFromCurrentPFParticleTimeX;   //!
   TBranch        *b_VertexFromCurrentPFParticleTimeY;   //!
   TBranch        *b_VertexFromCurrentPFParticleTimeZ;   //!

   TBranch        *b_MCParticle_Vx;   //!
   TBranch        *b_MCParticle_Vy;   //!
   TBranch        *b_MCParticle_Vz;   //!

   TBranch        *b_MCParticle_EndX;   //!
   TBranch        *b_MCParticle_EndY;   //!
   TBranch        *b_MCParticle_EndZ;   //!

   TBranch        *b_MCParticle_StatusCode;   //!
   TBranch        *b_MCParticle_Process;   //!   
   TBranch        *b_MCParticle_PdgCode;   //!
   TBranch        *b_MCParticle_P;   //!

   TBranch        *b_PFParticle_NuScore;   //!
   TBranch        *b_PFParticle_FlashScore;   //!

   //PreSelection(TTree *tree=0);
   PreSelection(TString WhichSample="", TChain *tree=0);

   virtual ~PreSelection();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);

   //virtual void     Init(TTree *tree);
   virtual void     Init(TChain *tree);

   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual string ToString(int num);
};

#endif

#ifdef PreSelection_cxx
PreSelection::PreSelection(TString WhichSample, TChain *tree) : fChain(0) 
//PreSelection::PreSelection(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(CCQEPath+File+".root");
//      if (!f || !f->IsOpen()) {
//         f = new TFile(CCQEPath+File+".root");
//      }
//      //TDirectory * dir = (TDirectory*)f->Get(CCQEPath+File+".root:/CaliTTCreatorFinder");
//      //dir->GetObject("myTTree",tree);
//      f->GetObject("myTTree",tree);

//   }
//   Init(tree);

	fWhichSample = WhichSample;

	TString CCQEPath = "/pnfs/uboone/persistent/users/apapadop/"+fWhichSample+"/"+UBCodeVersion+"/";

	TString Name = CCQEPath+"my"+fWhichSample+"_"+UBCodeVersion+"_Part";

	TChain* fmyLocalChain = new TChain("myTTree");

	fmyLocalChain->Add(Name+"*.root");

	tree = fmyLocalChain;
	std::cout << endl << "Total # " + fWhichSample  + " Entries = " << tree->GetEntries() << std::endl << std::endl;
	Init(tree);	

}

PreSelection::~PreSelection()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t PreSelection::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t PreSelection::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

//void PreSelection::Init(TTree *tree)
void PreSelection::Init(TChain *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   EventWeight = 0;
   T2KEventWeight = 0;
   ROOTinoEventWeight = 0; 

   All_UBGenie_EventWeight = 0;
   AxFFCCQEshape_UBGenie_EventWeight = 0;
   DecayAngMEC_UBGenie_EventWeight = 0;
   NormCCCOH_UBGenie_EventWeight = 0;
   NormNCCOH_UBGenie_EventWeight = 0;
//   RPA_CCQE_Reduced_UBGenie_EventWeight = 0;
   RPA_CCQE_UBGenie_EventWeight = 0;
   ThetaDelta2NRad_UBGenie_EventWeight = 0;
   Theta_Delta2Npi_UBGenie_EventWeight = 0;
   VecFFCCQEshape_UBGenie_EventWeight = 0;
   XSecShape_CCMEC_UBGenie_EventWeight = 0;
   expskin_FluxUnisim_EventWeight = 0;
   horncurrent_FluxUnisim_EventWeight = 0;
   kminus_PrimaryHadronNormalization_EventWeight = 0;
   kplus_PrimaryHadronFeynmanScaling_EventWeight = 0;
   kzero_PrimaryHadronSanfordWang_EventWeight = 0;
   nucleoninexsec_FluxUnisim_EventWeight = 0;
   nucleonqexsec_FluxUnisim_EventWeight = 0;
   nucleontotxsec_FluxUnisim_EventWeight = 0;
   piminus_PrimaryHadronSWCentralSplineVariation_EventWeight = 0;
   pioninexsec_FluxUnisim_EventWeight = 0;
   pionqexsec_FluxUnisim_EventWeight = 0;
   piontotxsec_FluxUnisim_EventWeight = 0;
   piplus_PrimaryHadronSWCentralSplineVariation_EventWeight = 0;
   reinteractions_piminus_Geant4_EventWeight = 0;
   reinteractions_piplus_Geant4_EventWeight = 0;
   reinteractions_proton_Geant4_EventWeight = 0;
//   xsr_scc_Fa3_SCC_EventWeight = 0;
//   xsr_scc_Fv3_SCC_EventWeight = 0;

   Track_Length = 0;
   Track_Phi = 0;
   Track_Theta = 0;
   Track_StartX = 0;
   Track_StartY = 0;
   Track_StartZ = 0;
   Track_EndX = 0;
   Track_EndY = 0;
   Track_EndZ = 0;
   Track_Momentum_MCS = 0;
   Track_Momentum_Range_Muon = 0;
   Track_Momentum_Range_Proton = 0;
   Track_IsBeamEvent = 0;
   Track_MCParticle_Mother = 0;
   Track_MCParticle_PdgCode = 0;
   Track_MCParticle_Vx = 0;
   Track_MCParticle_Vy = 0;
   Track_MCParticle_Vz = 0;
   Track_MCParticle_EndX = 0;
   Track_MCParticle_EndY = 0;
   Track_MCParticle_EndZ = 0;
//   Track_MCParticle_Process = 0;
   Track_MCParticle_E = 0;
   Track_MCParticle_P = 0;
   Track_MCParticle_Px = 0;
   Track_MCParticle_Py = 0;
   Track_MCParticle_Pz = 0;
   Track_MCParticle_Mass = 0;
   Track_MCParticle_Purity = 0;
   Track_MCParticle_Origin = 0;
/*   Track_AssMCTruth_NParticles = 0;
   Track_AssMCTruth_Nu_PdgCode = 0;
   Track_AssMCTruth_Lepton_PdgCode = 0;
   Track_AssMCTruth_CCNC = 0;
   Track_AssMCTruth_Mode = 0;*/
//   Track_MCParticle_InteractionType = 0;
//   Track_MCParticle_Mode = 0;
/*   Track_AssMCTruth_QSqr = 0;
   Track_AssMCTruth_X = 0;
   Track_AssMCTruth_Y = 0;
   Track_AssMCTruth_W = 0;*/
   /*Track_Calorimetry_Plane2_PlaneID = 0;
   Track_Calorimetry_Plane2_ResidualRange = 0;
   Track_Calorimetry_Plane2_dEdx = 0;
   Track_Calorimetry_Plane2_dQdx = 0;
   Track_Calorimetry_Plane2_TruncdEdx = 0;
   Track_Calorimetry_Plane2_TruncdQdx = 0;
   Track_Calorimetry_Plane2_CaliKineticEnergy = 0;
   Track_ParticleId_MinChi2 = 0;
   Track_ParticleId_Chi2Proton = 0;
   Track_ParticleId_Chi2Kaon = 0;
   Track_ParticleId_Chi2Pion = 0;
   Track_ParticleId_Chi2Muon = 0;
   Track_ParticleId_PIDA = 0;
   Track_ParticleId_Ndf = 0;
   Track_ParticleId_DeltaChi2 = 0;
   Track_ParticleId_MissingE = 0;
   Track_ParticleId_MissingEavg = 0;
   Track_ParticleId_PlaneID = 0;*/
   
/*   Track_PlaneID = 0;*/
/*   Track_Start_Wire = 0;*/
/*   Track_Start_Time = 0;*/
/*   Track_End_Wire = 0;*/
/*   Track_End_Time = 0;*/

   Track_NumberAssHits = 0;
   Track_AssHit_Integral = 0;
   Track_AssHit_PeakTime = 0;
   Track_AssHit_Wire = 0;
   Track_AssHit_WireID_Plane = 0;  

   Hit_Integral = 0;
   Hit_PeakTime = 0;
   Hit_Wire = 0;
   Hit_WireID_Plane = 0; 
   
   FlashesBeam_Time = 0;
/*   FlashesBeam_Twidth = 0;*/
/*   FlashesBeam_AbsTime = 0;
   FlashesBeam_Frame = 0;*/
   FlashesBeam_Ycenter = 0;
/*   FlashesBeam_Ywidth = 0;*/
   FlashesBeam_Zcenter = 0;
/*   FlashesBeam_Zwidth = 0;*/
   FlashesBeam_TotalPE = 0;
/*   FlashesBeam_WireCenters = 0;
   FlashesBeam_WireWidths = 0;
   FlashesBeam_FastToTotal = 0;*/
/*   MCParticle_AssMCTruth_QSqr = 0;
   MCParticle_AssMCTruth_X = 0;
   MCParticle_AssMCTruth_Y = 0;
   MCParticle_AssMCTruth_W = 0;*/

//   Track_ParticleId_MIPScore_ThreePlanePID = 0;
//   Track_ParticleId_MuonScore_ThreePlanePID = 0;
   Track_ParticleId_ProtonScore_ThreePlanePID = 0;
//   Track_ParticleId_PionScore_ThreePlanePID = 0;

//   Track_ParticleId_MIPScore_Chi2_YPlane = 0;
//   Track_ParticleId_MuonScore_Chi2_YPlane = 0;
   Track_ParticleId_ProtonScore_Chi2_YPlane = 0;
//   Track_ParticleId_PionScore_Chi2_YPlane = 0;

//   Track_ParticleId_MIPScore_Chi2_UPlane = 0;
//   Track_ParticleId_MuonScore_Chi2_UPlane = 0;
   Track_ParticleId_ProtonScore_Chi2_UPlane = 0;
//   Track_ParticleId_PionScore_Chi2_UPlane = 0;

//   Track_ParticleId_MIPScore_Chi2_VPlane = 0;
//   Track_ParticleId_MuonScore_Chi2_VPlane = 0;
   Track_ParticleId_ProtonScore_Chi2_VPlane = 0;
//   Track_ParticleId_PionScore_Chi2_VPlane = 0;

   Track_LLR_PID = 0;

   MCTruth_CCNC = 0;
   MCTruth_Mode = 0;
   MCTruth_InteractionType = 0;
   MCTruth_Particle_Nu_E = 0;
   MCTruth_Particle_Nu_Vx = 0;
   MCTruth_Particle_Nu_Vy = 0;
   MCTruth_Particle_Nu_Vz = 0;

   PFParticle_NumberNuMuDaughters = 0;
   PFParticle_NumberNuMuDaughtersPdgCode = 0;
   TracksFromCurrentPFParticleStartX = 0;
   TracksFromCurrentPFParticleTrackScore = 0; 
  
   VertexFromCurrentPFParticlePositionX = 0;
   VertexFromCurrentPFParticlePositionY = 0;   
   VertexFromCurrentPFParticlePositionZ = 0;

   VertexFromCurrentPFParticlePlaneX = 0;
   VertexFromCurrentPFParticlePlaneY = 0;
   VertexFromCurrentPFParticlePlaneZ = 0;

   VertexFromCurrentPFParticleWireX = 0;
   VertexFromCurrentPFParticleWireY = 0;
   VertexFromCurrentPFParticleWireZ = 0;

   VertexFromCurrentPFParticleTimeX = 0;
   VertexFromCurrentPFParticleTimeY = 0;
   VertexFromCurrentPFParticleTimeZ = 0;         

   MCParticle_Vx = 0;
   MCParticle_Vy = 0;
   MCParticle_Vz = 0;

   MCParticle_EndX = 0;
   MCParticle_EndY = 0;
   MCParticle_EndZ = 0;

   MCParticle_StatusCode = 0;
   MCParticle_Process = 0;   
   MCParticle_PdgCode = 0;
   MCParticle_P = 0;

   PFParticle_NuScore = 0;
   PFParticle_FlashScore = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventWeight", &EventWeight, &b_EventWeight);
   fChain->SetBranchAddress("T2KEventWeight", &T2KEventWeight, &b_T2KEventWeight);
   fChain->SetBranchAddress("ROOTinoEventWeight", &ROOTinoEventWeight, &b_ROOTinoEventWeight);   

   fChain->SetBranchAddress("All_UBGenie_EventWeight", &All_UBGenie_EventWeight, &b_All_UBGenie_EventWeight);
   fChain->SetBranchAddress("AxFFCCQEshape_UBGenie_EventWeight", &AxFFCCQEshape_UBGenie_EventWeight, &b_AxFFCCQEshape_UBGenie_EventWeight);
   fChain->SetBranchAddress("DecayAngMEC_UBGenie_EventWeight", &DecayAngMEC_UBGenie_EventWeight, &b_DecayAngMEC_UBGenie_EventWeight);
   fChain->SetBranchAddress("NormCCCOH_UBGenie_EventWeight", &NormCCCOH_UBGenie_EventWeight, &b_NormCCCOH_UBGenie_EventWeight);
   fChain->SetBranchAddress("NormNCCOH_UBGenie_EventWeight", &NormNCCOH_UBGenie_EventWeight, &b_NormNCCOH_UBGenie_EventWeight);
//   fChain->SetBranchAddress("RPA_CCQE_Reduced_UBGenie_EventWeight", &RPA_CCQE_Reduced_UBGenie_EventWeight, &b_RPA_CCQE_Reduced_UBGenie_EventWeight);
   fChain->SetBranchAddress("RPA_CCQE_UBGenie_EventWeight", &RPA_CCQE_UBGenie_EventWeight, &b_RPA_CCQE_UBGenie_EventWeight);
   fChain->SetBranchAddress("ThetaDelta2NRad_UBGenie_EventWeight", &ThetaDelta2NRad_UBGenie_EventWeight, &b_ThetaDelta2NRad_UBGenie_EventWeight);
   fChain->SetBranchAddress("Theta_Delta2Npi_UBGenie_EventWeight", &Theta_Delta2Npi_UBGenie_EventWeight, &b_Theta_Delta2Npi_UBGenie_EventWeight);
   fChain->SetBranchAddress("VecFFCCQEshape_UBGenie_EventWeight", &VecFFCCQEshape_UBGenie_EventWeight, &b_VecFFCCQEshape_UBGenie_EventWeight);
   fChain->SetBranchAddress("XSecShape_CCMEC_UBGenie_EventWeight", &XSecShape_CCMEC_UBGenie_EventWeight, &b_XSecShape_CCMEC_UBGenie_EventWeight);
   fChain->SetBranchAddress("expskin_FluxUnisim_EventWeight", &expskin_FluxUnisim_EventWeight, &b_expskin_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("horncurrent_FluxUnisim_EventWeight", &horncurrent_FluxUnisim_EventWeight, &b_horncurrent_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("kminus_PrimaryHadronNormalization_EventWeight", &kminus_PrimaryHadronNormalization_EventWeight, &b_kminus_PrimaryHadronNormalization_EventWeight);
   fChain->SetBranchAddress("kplus_PrimaryHadronFeynmanScaling_EventWeight", &kplus_PrimaryHadronFeynmanScaling_EventWeight, &b_kplus_PrimaryHadronFeynmanScaling_EventWeight);
   fChain->SetBranchAddress("kzero_PrimaryHadronSanfordWang_EventWeight", &kzero_PrimaryHadronSanfordWang_EventWeight, &b_kzero_PrimaryHadronSanfordWang_EventWeight);
   fChain->SetBranchAddress("nucleoninexsec_FluxUnisim_EventWeight", &nucleoninexsec_FluxUnisim_EventWeight, &b_nucleoninexsec_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("nucleonqexsec_FluxUnisim_EventWeight", &nucleonqexsec_FluxUnisim_EventWeight, &b_nucleonqexsec_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("nucleontotxsec_FluxUnisim_EventWeight", &nucleontotxsec_FluxUnisim_EventWeight, &b_nucleontotxsec_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("piminus_PrimaryHadronSWCentralSplineVariation_EventWeight", &piminus_PrimaryHadronSWCentralSplineVariation_EventWeight, &b_piminus_PrimaryHadronSWCentralSplineVariation_EventWeight);
   fChain->SetBranchAddress("pioninexsec_FluxUnisim_EventWeight", &pioninexsec_FluxUnisim_EventWeight, &b_pioninexsec_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("pionqexsec_FluxUnisim_EventWeight", &pionqexsec_FluxUnisim_EventWeight, &b_pionqexsec_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("piontotxsec_FluxUnisim_EventWeight", &piontotxsec_FluxUnisim_EventWeight, &b_piontotxsec_FluxUnisim_EventWeight);
   fChain->SetBranchAddress("piplus_PrimaryHadronSWCentralSplineVariation_EventWeight", &piplus_PrimaryHadronSWCentralSplineVariation_EventWeight, &b_piplus_PrimaryHadronSWCentralSplineVariation_EventWeight);
   fChain->SetBranchAddress("reinteractions_piminus_Geant4_EventWeight", &reinteractions_piminus_Geant4_EventWeight, &b_reinteractions_piminus_Geant4_EventWeight);
   fChain->SetBranchAddress("reinteractions_piplus_Geant4_EventWeight", &reinteractions_piplus_Geant4_EventWeight, &b_reinteractions_piplus_Geant4_EventWeight);
   fChain->SetBranchAddress("reinteractions_proton_Geant4_EventWeight", &reinteractions_proton_Geant4_EventWeight, &b_reinteractions_proton_Geant4_EventWeight);
//   fChain->SetBranchAddress("xsr_scc_Fa3_SCC_EventWeight", &xsr_scc_Fa3_SCC_EventWeight, &b_xsr_scc_Fa3_SCC_EventWeight);
//   fChain->SetBranchAddress("xsr_scc_Fv3_SCC_EventWeight", &xsr_scc_Fv3_SCC_EventWeight, &b_xsr_scc_Fv3_SCC_EventWeight);

   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
   fChain->SetBranchAddress("SubRunNumber", &SubRunNumber, &b_SubRunNumber);
   fChain->SetBranchAddress("EventNumber", &EventNumber, &b_EventNumber);
   fChain->SetBranchAddress("ientry", &ientry, &b_ientry);
   fChain->SetBranchAddress("EventPassedSwTrigger", &EventPassedSwTrigger, &b_EventPassedSwTrigger);
   fChain->SetBranchAddress("NumberTracks", &NumberTracks, &b_NumberTracks);
   fChain->SetBranchAddress("Track_Length", &Track_Length, &b_Track_Length);
   fChain->SetBranchAddress("Track_Phi", &Track_Phi, &b_Track_Phi);
   fChain->SetBranchAddress("Track_Theta", &Track_Theta, &b_Track_Theta);
   fChain->SetBranchAddress("Track_StartX", &Track_StartX, &b_Track_StartX);
   fChain->SetBranchAddress("Track_StartY", &Track_StartY, &b_Track_StartY);
   fChain->SetBranchAddress("Track_StartZ", &Track_StartZ, &b_Track_StartZ);
   fChain->SetBranchAddress("Track_EndX", &Track_EndX, &b_Track_EndX);
   fChain->SetBranchAddress("Track_EndY", &Track_EndY, &b_Track_EndY);
   fChain->SetBranchAddress("Track_EndZ", &Track_EndZ, &b_Track_EndZ);
   fChain->SetBranchAddress("Track_Momentum_MCS", &Track_Momentum_MCS, &b_Track_Momentum_MCS);
   fChain->SetBranchAddress("Track_Momentum_Range_Muon", &Track_Momentum_Range_Muon, &b_Track_Momentum_Range_Muon);
   fChain->SetBranchAddress("Track_Momentum_Range_Proton", &Track_Momentum_Range_Proton, &b_Track_Momentum_Range_Proton);
   fChain->SetBranchAddress("Track_IsBeamEvent", &Track_IsBeamEvent, &b_Track_IsBeamEvent);
   fChain->SetBranchAddress("Track_MCParticle_Mother", &Track_MCParticle_Mother, &b_Track_MCParticle_Mother);
   fChain->SetBranchAddress("Track_MCParticle_PdgCode", &Track_MCParticle_PdgCode, &b_Track_MCParticle_PdgCode);
   fChain->SetBranchAddress("Track_MCParticle_Vx", &Track_MCParticle_Vx, &b_Track_MCParticle_Vx);
   fChain->SetBranchAddress("Track_MCParticle_Vy", &Track_MCParticle_Vy, &b_Track_MCParticle_Vy);
   fChain->SetBranchAddress("Track_MCParticle_Vz", &Track_MCParticle_Vz, &b_Track_MCParticle_Vz);
   fChain->SetBranchAddress("Track_MCParticle_EndX", &Track_MCParticle_EndX, &b_Track_MCParticle_EndX);
   fChain->SetBranchAddress("Track_MCParticle_EndY", &Track_MCParticle_EndY, &b_Track_MCParticle_EndY);
   fChain->SetBranchAddress("Track_MCParticle_EndZ", &Track_MCParticle_EndZ, &b_Track_MCParticle_EndZ);
//   fChain->SetBranchAddress("Track_MCParticle_Process", &Track_MCParticle_Process, &b_Track_MCParticle_Process);
   fChain->SetBranchAddress("Track_MCParticle_E", &Track_MCParticle_E, &b_Track_MCParticle_E);
   fChain->SetBranchAddress("Track_MCParticle_P", &Track_MCParticle_P, &b_Track_MCParticle_P);
   fChain->SetBranchAddress("Track_MCParticle_Px", &Track_MCParticle_Px, &b_Track_MCParticle_Px);
   fChain->SetBranchAddress("Track_MCParticle_Py", &Track_MCParticle_Py, &b_Track_MCParticle_Py);
   fChain->SetBranchAddress("Track_MCParticle_Pz", &Track_MCParticle_Pz, &b_Track_MCParticle_Pz);
   fChain->SetBranchAddress("Track_MCParticle_Mass", &Track_MCParticle_Mass, &b_Track_MCParticle_Mass);
   fChain->SetBranchAddress("Track_MCParticle_Purity", &Track_MCParticle_Purity, &b_Track_MCParticle_Purity);
   fChain->SetBranchAddress("Track_MCParticle_Origin", &Track_MCParticle_Origin, &b_Track_MCParticle_Origin);
/*   fChain->SetBranchAddress("Track_AssMCTruth_NParticles", &Track_AssMCTruth_NParticles, &b_Track_AssMCTruth_NParticles);
   fChain->SetBranchAddress("Track_AssMCTruth_Nu_PdgCode", &Track_AssMCTruth_Nu_PdgCode, &b_Track_AssMCTruth_Nu_PdgCode);
   fChain->SetBranchAddress("Track_AssMCTruth_Lepton_PdgCode", &Track_AssMCTruth_Lepton_PdgCode, &b_Track_AssMCTruth_Lepton_PdgCode);
   fChain->SetBranchAddress("Track_AssMCTruth_CCNC", &Track_AssMCTruth_CCNC, &b_Track_AssMCTruth_CCNC);
   fChain->SetBranchAddress("Track_AssMCTruth_Mode", &Track_AssMCTruth_Mode, &b_Track_AssMCTruth_Mode);*/
//   fChain->SetBranchAddress("Track_MCParticle_InteractionType", &Track_MCParticle_InteractionType, &b_Track_MCParticle_InteractionType);
//   fChain->SetBranchAddress("Track_MCParticle_Mode", &Track_MCParticle_Mode, &b_Track_MCParticle_Mode);
/*   fChain->SetBranchAddress("Track_AssMCTruth_QSqr", &Track_AssMCTruth_QSqr, &b_Track_AssMCTruth_QSqr);
   fChain->SetBranchAddress("Track_AssMCTruth_X", &Track_AssMCTruth_X, &b_Track_AssMCTruth_X);
   fChain->SetBranchAddress("Track_AssMCTruth_Y", &Track_AssMCTruth_Y, &b_Track_AssMCTruth_Y);
   fChain->SetBranchAddress("Track_AssMCTruth_W", &Track_AssMCTruth_W, &b_Track_AssMCTruth_W);*/
   /*fChain->SetBranchAddress("Track_Calorimetry_Plane2_PlaneID", &Track_Calorimetry_Plane2_PlaneID, &b_Track_Calorimetry_Plane2_PlaneID);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_ResidualRange", &Track_Calorimetry_Plane2_ResidualRange, &b_Track_Calorimetry_Plane2_ResidualRange);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_dEdx", &Track_Calorimetry_Plane2_dEdx, &b_Track_Calorimetry_Plane2_dEdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_dQdx", &Track_Calorimetry_Plane2_dQdx, &b_Track_Calorimetry_Plane2_dQdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_TruncdEdx", &Track_Calorimetry_Plane2_TruncdEdx, &b_Track_Calorimetry_Plane2_TruncdEdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_TruncdQdx", &Track_Calorimetry_Plane2_TruncdQdx, &b_Track_Calorimetry_Plane2_TruncdQdx);
   fChain->SetBranchAddress("Track_Calorimetry_Plane2_CaliKineticEnergy", &Track_Calorimetry_Plane2_CaliKineticEnergy, &b_Track_Calorimetry_Plane2_CaliKineticEnergy);
   fChain->SetBranchAddress("Track_ParticleId_Pdg", &Track_ParticleId_Pdg, &b_Track_ParticleId_Pdg);
   fChain->SetBranchAddress("Track_ParticleId_MinChi2", &Track_ParticleId_MinChi2, &b_Track_ParticleId_MinChi2);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Proton", &Track_ParticleId_Chi2Proton, &b_Track_ParticleId_Chi2Proton);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Kaon", &Track_ParticleId_Chi2Kaon, &b_Track_ParticleId_Chi2Kaon);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Pion", &Track_ParticleId_Chi2Pion, &b_Track_ParticleId_Chi2Pion);
   fChain->SetBranchAddress("Track_ParticleId_Chi2Muon", &Track_ParticleId_Chi2Muon, &b_Track_ParticleId_Chi2Muon);
   fChain->SetBranchAddress("Track_ParticleId_PIDA", &Track_ParticleId_PIDA, &b_Track_ParticleId_PIDA);
   fChain->SetBranchAddress("Track_ParticleId_Ndf", &Track_ParticleId_Ndf, &b_Track_ParticleId_Ndf);
   fChain->SetBranchAddress("Track_ParticleId_DeltaChi2", &Track_ParticleId_DeltaChi2, &b_Track_ParticleId_DeltaChi2);
   fChain->SetBranchAddress("Track_ParticleId_MissingE", &Track_ParticleId_MissingE, &b_Track_ParticleId_MissingE);
   fChain->SetBranchAddress("Track_ParticleId_MissingEavg", &Track_ParticleId_MissingEavg, &b_Track_ParticleId_MissingEavg);
   fChain->SetBranchAddress("Track_ParticleId_PlaneID", &Track_ParticleId_PlaneID, &b_Track_ParticleId_PlaneID);*/
   fChain->SetBranchAddress("NumberFlashesBeam", &NumberFlashesBeam, &b_NumberFlashesBeam);
   
/*   fChain->SetBranchAddress("Track_PlaneID", &Track_PlaneID, &b_Track_PlaneID);*/
/*   fChain->SetBranchAddress("Track_Start_Wire", &Track_Start_Wire, &b_Track_Start_Wire);*/
/*   fChain->SetBranchAddress("Track_Start_Time", &Track_Start_Time, &b_Track_Start_Time);*/
/*   fChain->SetBranchAddress("Track_End_Wire", &Track_End_Wire, &b_Track_End_Wire);*/
/*   fChain->SetBranchAddress("Track_End_Time", &Track_End_Time, &b_Track_End_Time);*/

   fChain->SetBranchAddress("Track_NumberAssHits", &Track_NumberAssHits, &b_Track_NumberAssHits);
   fChain->SetBranchAddress("Track_AssHit_Integral", &Track_AssHit_Integral, &b_Track_AssHit_Integral);
   fChain->SetBranchAddress("Track_AssHit_PeakTime", &Track_AssHit_PeakTime, &b_Track_AssHit_PeakTime);
   fChain->SetBranchAddress("Track_AssHit_Wire", &Track_AssHit_Wire, &b_Track_AssHit_Wire);
   fChain->SetBranchAddress("Track_AssHit_WireID_Plane", &Track_AssHit_WireID_Plane, &b_Track_AssHit_WireID_Plane);
 
   fChain->SetBranchAddress("NumberHits", &NumberHits, &b_NumberHits);
   fChain->SetBranchAddress("Hit_Integral", &Hit_Integral, &b_Hit_Integral);
   fChain->SetBranchAddress("Hit_PeakTime", &Hit_PeakTime, &b_Hit_PeakTime);
   fChain->SetBranchAddress("Hit_Wire", &Hit_Wire, &b_Hit_Wire);
   fChain->SetBranchAddress("Hit_WireID_Plane", &Hit_WireID_Plane, &b_Hit_WireID_Plane);  
   
   fChain->SetBranchAddress("FlashesBeam_Time", &FlashesBeam_Time, &b_FlashesBeam_Time);
/*   fChain->SetBranchAddress("FlashesBeam_Twidth", &FlashesBeam_Twidth, &b_FlashesBeam_Twidth);*/
/*   fChain->SetBranchAddress("FlashesBeam_AbsTime", &FlashesBeam_AbsTime, &b_FlashesBeam_AbsTime);
   fChain->SetBranchAddress("FlashesBeam_Frame", &FlashesBeam_Frame, &b_FlashesBeam_Frame);*/
   fChain->SetBranchAddress("FlashesBeam_Ycenter", &FlashesBeam_Ycenter, &b_FlashesBeam_Ycenter);
/*   fChain->SetBranchAddress("FlashesBeam_Ywidth", &FlashesBeam_Ywidth, &b_FlashesBeam_Ywidth);*/
   fChain->SetBranchAddress("FlashesBeam_Zcenter", &FlashesBeam_Zcenter, &b_FlashesBeam_Zcenter);
//   fChain->SetBranchAddress("FlashesBeam_Zwidth", &FlashesBeam_Zwidth, &b_FlashesBeam_Zwidth);
   fChain->SetBranchAddress("FlashesBeam_TotalPE", &FlashesBeam_TotalPE, &b_FlashesBeam_TotalPE);
/*   fChain->SetBranchAddress("FlashesBeam_WireCenters", &FlashesBeam_WireCenters, &b_FlashesBeam_WireCenters);
   fChain->SetBranchAddress("FlashesBeam_WireWidths", &FlashesBeam_WireWidths, &b_FlashesBeam_WireWidths);
   fChain->SetBranchAddress("FlashesBeam_FastToTotal", &FlashesBeam_FastToTotal, &b_FlashesBeam_FastToTotal);*/
/*   fChain->SetBranchAddress("MCParticle_AssMCTruth_QSqr", &MCParticle_AssMCTruth_QSqr, &b_MCParticle_AssMCTruth_QSqr);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_X", &MCParticle_AssMCTruth_X, &b_MCParticle_AssMCTruth_X);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_Y", &MCParticle_AssMCTruth_Y, &b_MCParticle_AssMCTruth_Y);
   fChain->SetBranchAddress("MCParticle_AssMCTruth_W", &MCParticle_AssMCTruth_W, &b_MCParticle_AssMCTruth_W);*/

//   fChain->SetBranchAddress("Track_ParticleId_MIPScore_ThreePlanePID", &Track_ParticleId_MIPScore_ThreePlanePID, &b_Track_ParticleId_MIPScore_ThreePlanePID);
//   fChain->SetBranchAddress("Track_ParticleId_MuonScore_ThreePlanePID", &Track_ParticleId_MuonScore_ThreePlanePID, &b_Track_ParticleId_MuonScore_ThreePlanePID);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_ThreePlanePID", &Track_ParticleId_ProtonScore_ThreePlanePID, &b_Track_ParticleId_ProtonScore_ThreePlanePID);
//   fChain->SetBranchAddress("Track_ParticleId_PionScore_ThreePlanePID", &Track_ParticleId_PionScore_ThreePlanePID, &b_Track_ParticleId_PionScore_ThreePlanePID);

//   fChain->SetBranchAddress("Track_ParticleId_MIPScore_Chi2_YPlane", &Track_ParticleId_MIPScore_Chi2_YPlane, &b_Track_ParticleId_MIPScore_Chi2_YPlane);
//   fChain->SetBranchAddress("Track_ParticleId_MuonScore_Chi2_YPlane", &Track_ParticleId_MuonScore_Chi2_YPlane, &b_Track_ParticleId_MuonScore_Chi2_YPlane);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_Chi2_YPlane", &Track_ParticleId_ProtonScore_Chi2_YPlane, &b_Track_ParticleId_ProtonScore_Chi2_YPlane);
//   fChain->SetBranchAddress("Track_ParticleId_PionScore_Chi2_YPlane", &Track_ParticleId_PionScore_Chi2_YPlane, &b_Track_ParticleId_PionScore_Chi2_YPlane);

//   fChain->SetBranchAddress("Track_ParticleId_MIPScore_Chi2_UPlane", &Track_ParticleId_MIPScore_Chi2_UPlane, &b_Track_ParticleId_MIPScore_Chi2_UPlane);
//   fChain->SetBranchAddress("Track_ParticleId_MuonScore_Chi2_UPlane", &Track_ParticleId_MuonScore_Chi2_UPlane, &b_Track_ParticleId_MuonScore_Chi2_UPlane);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_Chi2_UPlane", &Track_ParticleId_ProtonScore_Chi2_UPlane, &b_Track_ParticleId_ProtonScore_Chi2_UPlane);
//   fChain->SetBranchAddress("Track_ParticleId_PionScore_Chi2_UPlane", &Track_ParticleId_PionScore_Chi2_UPlane, &b_Track_ParticleId_PionScore_Chi2_UPlane);

//   fChain->SetBranchAddress("Track_ParticleId_MIPScore_Chi2_VPlane", &Track_ParticleId_MIPScore_Chi2_VPlane, &b_Track_ParticleId_MIPScore_Chi2_VPlane);
//   fChain->SetBranchAddress("Track_ParticleId_MuonScore_Chi2_VPlane", &Track_ParticleId_MuonScore_Chi2_VPlane, &b_Track_ParticleId_MuonScore_Chi2_VPlane);
   fChain->SetBranchAddress("Track_ParticleId_ProtonScore_Chi2_VPlane", &Track_ParticleId_ProtonScore_Chi2_VPlane, &b_Track_ParticleId_ProtonScore_Chi2_VPlane);
//   fChain->SetBranchAddress("Track_ParticleId_PionScore_Chi2_VPlane", &Track_ParticleId_PionScore_Chi2_VPlane, &b_Track_ParticleId_PionScore_Chi2_VPlane);

   fChain->SetBranchAddress("Track_LLR_PID", &Track_LLR_PID, &b_Track_LLR_PID);

   fChain->SetBranchAddress("MCTruth_CCNC", &MCTruth_CCNC, &b_MCTruth_CCNC);
   fChain->SetBranchAddress("MCTruth_Mode", &MCTruth_Mode, &b_MCTruth_Mode);
   fChain->SetBranchAddress("MCTruth_InteractionType", &MCTruth_InteractionType, &b_MCTruth_InteractionType);
   fChain->SetBranchAddress("MCTruth_Particle_Nu_E", &MCTruth_Particle_Nu_E, &b_MCTruth_Particle_Nu_E);
   fChain->SetBranchAddress("MCTruth_Particle_Nu_Vx", &MCTruth_Particle_Nu_Vx, &b_MCTruth_Particle_Nu_Vx);
   fChain->SetBranchAddress("MCTruth_Particle_Nu_Vy", &MCTruth_Particle_Nu_Vy, &b_MCTruth_Particle_Nu_Vy);
   fChain->SetBranchAddress("MCTruth_Particle_Nu_Vz", &MCTruth_Particle_Nu_Vz, &b_MCTruth_Particle_Nu_Vz);

   fChain->SetBranchAddress("NumberNuMuPFParticles", &NumberNuMuPFParticles, &b_NumberNuMuPFParticles);

   fChain->SetBranchAddress("PFParticle_NumberNuMuDaughters", &PFParticle_NumberNuMuDaughters, &b_PFParticle_NumberNuMuDaughters);
   fChain->SetBranchAddress("PFParticle_NumberNuMuDaughtersPdgCode", &PFParticle_NumberNuMuDaughtersPdgCode, &b_PFParticle_NumberNuMuDaughtersPdgCode);
   fChain->SetBranchAddress("TracksFromCurrentPFParticleStartX", &TracksFromCurrentPFParticleStartX, &b_TracksFromCurrentPFParticleStartX);
   fChain->SetBranchAddress("TracksFromCurrentPFParticleTrackScore", &TracksFromCurrentPFParticleTrackScore, &b_TracksFromCurrentPFParticleTrackScore);

   fChain->SetBranchAddress("VertexFromCurrentPFParticlePositionX", &VertexFromCurrentPFParticlePositionX, &b_VertexFromCurrentPFParticlePositionX);
   fChain->SetBranchAddress("VertexFromCurrentPFParticlePositionY", &VertexFromCurrentPFParticlePositionY, &b_VertexFromCurrentPFParticlePositionY);
   fChain->SetBranchAddress("VertexFromCurrentPFParticlePositionZ", &VertexFromCurrentPFParticlePositionZ, &b_VertexFromCurrentPFParticlePositionZ);

   fChain->SetBranchAddress("VertexFromCurrentPFParticlePlaneX", &VertexFromCurrentPFParticlePlaneX, &b_VertexFromCurrentPFParticlePlaneX);
   fChain->SetBranchAddress("VertexFromCurrentPFParticlePlaneY", &VertexFromCurrentPFParticlePlaneY, &b_VertexFromCurrentPFParticlePlaneY);
   fChain->SetBranchAddress("VertexFromCurrentPFParticlePlaneZ", &VertexFromCurrentPFParticlePlaneZ, &b_VertexFromCurrentPFParticlePlaneZ);

   fChain->SetBranchAddress("VertexFromCurrentPFParticleWireX", &VertexFromCurrentPFParticleWireX, &b_VertexFromCurrentPFParticleWireX);
   fChain->SetBranchAddress("VertexFromCurrentPFParticleWireY", &VertexFromCurrentPFParticleWireY, &b_VertexFromCurrentPFParticleWireY);
   fChain->SetBranchAddress("VertexFromCurrentPFParticleWireZ", &VertexFromCurrentPFParticleWireZ, &b_VertexFromCurrentPFParticleWireZ);

   fChain->SetBranchAddress("VertexFromCurrentPFParticleTimeX", &VertexFromCurrentPFParticleTimeX, &b_VertexFromCurrentPFParticleTimeX);
   fChain->SetBranchAddress("VertexFromCurrentPFParticleTimeY", &VertexFromCurrentPFParticleTimeY, &b_VertexFromCurrentPFParticleTimeY);
   fChain->SetBranchAddress("VertexFromCurrentPFParticleTimeZ", &VertexFromCurrentPFParticleTimeZ, &b_VertexFromCurrentPFParticleTimeZ);

   fChain->SetBranchAddress("MCParticle_Vx", &MCParticle_Vx, &b_MCParticle_Vx);
   fChain->SetBranchAddress("MCParticle_Vy", &MCParticle_Vy, &b_MCParticle_Vy);
   fChain->SetBranchAddress("MCParticle_Vz", &MCParticle_Vz, &b_MCParticle_Vz);

   fChain->SetBranchAddress("MCParticle_EndX", &MCParticle_EndX, &b_MCParticle_EndX);
   fChain->SetBranchAddress("MCParticle_EndY", &MCParticle_EndY, &b_MCParticle_EndY);
   fChain->SetBranchAddress("MCParticle_EndZ", &MCParticle_EndZ, &b_MCParticle_EndZ);

   fChain->SetBranchAddress("MCParticle_StatusCode", &MCParticle_StatusCode, &b_MCParticle_StatusCode);
   fChain->SetBranchAddress("MCParticle_Process", &MCParticle_Process, &b_MCParticle_Process);   
   fChain->SetBranchAddress("MCParticle_PdgCode", &MCParticle_PdgCode, &b_MCParticle_PdgCode);
   fChain->SetBranchAddress("MCParticle_P", &MCParticle_P, &b_MCParticle_P);

   fChain->SetBranchAddress("PFParticle_NuScore", &PFParticle_NuScore, &b_PFParticle_NuScore);
   fChain->SetBranchAddress("PFParticle_FlashScore", &PFParticle_FlashScore, &b_PFParticle_FlashScore);

   Notify();
}

Bool_t PreSelection::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void PreSelection::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t PreSelection::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

string PreSelection::ToString(int num) {

	std::ostringstream start;
	start << num;
	string start1 = start.str();
	return start1;

}

#endif // #ifdef PreSelection_cxx
