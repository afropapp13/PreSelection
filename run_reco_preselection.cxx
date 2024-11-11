{

	//pnfsToXRootD /pnfs/persistent/path/to/your/file

	vector<TString> WhichSampleArray; vector<TString> SamplePath; 

	// ---------------------------------------------------------------------------------- //
	// ---------------------------------------------------------------------------------- //

	// CV

	// Full BeamOn Samples

	WhichSampleArray.push_back("BeamOn9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/bnb_beam_on_peleeTuple_uboone_v08_00_00_70_run1_C1.root");
	WhichSampleArray.push_back("BeamOn9_Run1A_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1_opentrigger/run1_beamon_opentrigger_bnb_pandora_3v_a_reprocessing_v08_00_00_83_ntuple_ntuple_ana.root");
	WhichSampleArray.push_back("BeamOn9_Run1B_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1_opentrigger/run1_beamon_opentrigger_bnb_pandora_3v_b_reprocessing_v08_00_00_83_beam_good_ntuple_ntuple_ana.root");
	WhichSampleArray.push_back("BeamOn9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run2/bnb_beam_on_peleeTuple_uboone_v08_00_00_70_run2.root");
	WhichSampleArray.push_back("BeamOn9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/run3_bnb_beam_on_crtremerging_pandora_reco2_run3_ana.root");
	WhichSampleArray.push_back("BeamOn9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_bnb_beamOn_PeLee_ntuples_run4a_ana.root");
	WhichSampleArray.push_back("BeamOn9_Run4b"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/run4b_bnb_beamon_crtremerging_pandora_reco2_run4b_ana.root");
	WhichSampleArray.push_back("BeamOn9_Run4c"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/run4c_bnb_beamon_crtremerging_pandora_reco2_run4c_ana.root");
	WhichSampleArray.push_back("BeamOn9_Run4d"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_bnb_beamOn_PeLee_ntuples_run4d_ana_ana.root");
	WhichSampleArray.push_back("BeamOn9_Run5"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/run5_bnb_beamon_PeLEE_ntuples_run5_ana.root");				

	// ExtBNB

	WhichSampleArray.push_back("ExtBNB9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run1.root");
	WhichSampleArray.push_back("ExtBNB9_Run1A_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run1.root");
	WhichSampleArray.push_back("ExtBNB9_Run1B_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run1.root");
	WhichSampleArray.push_back("ExtBNB9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run2/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run2.root");
	WhichSampleArray.push_back("ExtBNB9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/bnb_beam_off_peleeTuple_uboone_v08_00_00_70_run3.root");
	WhichSampleArray.push_back("ExtBNB9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_bnb_beamOff_PeLee_ntuples_run4a_ana.root");
	WhichSampleArray.push_back("ExtBNB9_Run4b"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/fix_bnb_beam_off_pandora_reco2_crt_remerging_run4b_ana.root");
	WhichSampleArray.push_back("ExtBNB9_Run4c"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/run4c_bnb_beam_off_crtremerging_pandora_reco2_run4c_ana.root");
	WhichSampleArray.push_back("ExtBNB9_Run4d"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_bnb_beamOff_PeLee_ntuples_run4d_ana_ana.root");
	WhichSampleArray.push_back("ExtBNB9_Run5"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/Run5_bnb_beamOff_PeLee_ntuples_run5_ana_ana.root");			
	
	// MC CV

	WhichSampleArray.push_back("Overlay9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/overlay_peleeTuple_uboone_v08_00_00_70_run1_nu.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/overlay_peleeTuple_uboone_v08_00_00_70_run1_nu.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/overlay_peleeTuple_uboone_v08_00_00_70_run1_nu.root");
	WhichSampleArray.push_back("Overlay9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run2/overlay_peleeTuple_uboone_v08_00_00_70_run2_nu.root");
	WhichSampleArray.push_back("Overlay9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/overlay_peleeTuple_uboone_v08_00_00_70_run3_nu.root");
	WhichSampleArray.push_back("Overlay9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/run4a_bnb_nu_overlay_unified_pandora_reco2_run4a_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/run4b_bnb_nu_overlay_unified_pandora_reco2_run4b_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/overlay_peleeTuple_uboone_v08_00_00_70_run4c_nu.root");
	WhichSampleArray.push_back("Overlay9_Run4d"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/overlay_peleeTuple_uboone_v08_00_00_70_run4d_nu.root");
	WhichSampleArray.push_back("Overlay9_Run5"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/run5_bnb_nu_overlay_ntuple_v08_00_00_67_run5_ana.root");

	// Dirt

	WhichSampleArray.push_back("OverlayDirt9_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/overlay_peleeTuple_uboone_v08_00_00_70_run1_dirt.root");
	WhichSampleArray.push_back("OverlayDirt9_Run1A_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/overlay_peleeTuple_uboone_v08_00_00_70_run1_dirt.root");
	WhichSampleArray.push_back("OverlayDirt9_Run1B_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/overlay_peleeTuple_uboone_v08_00_00_70_run1_dirt.root");
	WhichSampleArray.push_back("OverlayDirt9_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run2/overlay_peleeTuple_uboone_v08_00_00_70_run2a_dirt.root");
	WhichSampleArray.push_back("OverlayDirt9_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/overlay_peleeTuple_uboone_v08_00_00_70_run3_dirt.root");
	WhichSampleArray.push_back("OverlayDirt9_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/Run4a_BNB_dirt_overlay_Pandora_Unified_Reco2_fixed_run4a_ana.root");
	WhichSampleArray.push_back("OverlayDirt9_Run4b"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4b/Run4b_BNB_dirt_overlay_Pandora_Reco2_reco2_ana.root");
	WhichSampleArray.push_back("OverlayDirt9_Run4c"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/overlay_peleeTuple_uboone_v08_00_00_70_run4c_dirt.root");
	WhichSampleArray.push_back("OverlayDirt9_Run4d"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4d/Run4d_BNB_dirt_overlay_Pandora_Unified_Reco2_reco2_ana.root");
	WhichSampleArray.push_back("OverlayDirt9_Run5"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/overlay_peleeTuple_uboone_v08_00_00_70_run5_dirt.root");		
	
	// ---------------------------------------------------------------------------------- //
	// ---------------------------------------------------------------------------------- //

	// NuWro

	WhichSampleArray.push_back("Overlay9NuWro_Run1"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run1_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run1A_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run1_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run1B_open_trigger"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run1/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run1_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run2/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run2_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run3"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3/high_stat_prodgenie_bnb_nu_overlay_DetVar_Run3_NuWro_reco2_reco2.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run4a"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4a/high_stat_prodgenie_bnb_nu_nuwro_overlay_run4a_pelee.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run4b"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/high_stat_prodgenie_bnb_nu_nuwro_overlay_run4_pelee.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run4c"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/high_stat_prodgenie_bnb_nu_nuwro_overlay_run4_pelee.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run4d"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4c/high_stat_prodgenie_bnb_nu_nuwro_overlay_run4_pelee.root");
	WhichSampleArray.push_back("Overlay9NuWro_Run5"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5/high_stat_prodgenie_bnb_nu_nuwro_overlay_run5_pelee.root");

	// ---------------------------------------------------------------------------------- //
	// ---------------------------------------------------------------------------------- //

	// Run1
	// Using the Run3 detector variations with Run1 scaling

	WhichSampleArray.push_back("Overlay9_Run1_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CV_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CVExtra_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYDown_reprocess_ana.root");	
	WhichSampleArray.push_back("Overlay9_Run1_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYRayleigh_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYAttenuation_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_SCE_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_Recomb2_reprocess_ana.root");

WhichSampleArray.push_back("Overlay9_Run1_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModX_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModYZ_reprocess_ana.root");
WhichSampleArray.push_back("Overlay9_Run1_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaXZ_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaYZ_reprocess_ana.root");

	// Run1A_open_trigger
	// Using the Run3 detector variations with Run1A_open_trigger scaling

	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CV_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CVExtra_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYDown_reprocess_ana.root");	
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYRayleigh_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYAttenuation_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_SCE_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_Recomb2_reprocess_ana.root");

	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModX_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModYZ_reprocess_ana.root");
WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaXZ_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1A_open_trigger_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaYZ_reprocess_ana.root");
	
	// Run1B_open_trigger
	// Using the Run3 detector variations with Run1B_open_trigger scaling

	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CV_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CVExtra_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYDown_reprocess_ana.root");	
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYRayleigh_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYAttenuation_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_SCE_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_Recomb2_reprocess_ana.root");

	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModX_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModYZ_reprocess_ana.root");
WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaXZ_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run1B_open_trigger_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaYZ_reprocess_ana.root");
		
	// Run2
	// Using the Run3 files with Run2 scaling

	WhichSampleArray.push_back("Overlay9_Run2_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CV_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run2_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CVExtra_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run2_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYDown_reprocess_ana.root");	
	WhichSampleArray.push_back("Overlay9_Run2_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYRayleigh_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run2_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYAttenuation_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run2_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_SCE_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run2_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_Recomb2_reprocess_ana.root");

WhichSampleArray.push_back("Overlay9_Run2_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModX_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run2_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModYZ_reprocess_ana.root");
WhichSampleArray.push_back("Overlay9_Run2_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaXZ_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run2_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaYZ_reprocess_ana.root");
	

	// Run3

	WhichSampleArray.push_back("Overlay9_Run3_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CV_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run3_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_CVExtra_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run3_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYDown_reprocess_ana.root");	
	WhichSampleArray.push_back("Overlay9_Run3_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYRayleigh_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run3_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_LYAttenuation_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run3_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_SCE_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run3_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_Recomb2_reprocess_ana.root");

WhichSampleArray.push_back("Overlay9_Run3_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModX_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run3_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModYZ_reprocess_ana.root");
WhichSampleArray.push_back("Overlay9_Run3_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaXZ_reprocess_ana.root");
	WhichSampleArray.push_back("Overlay9_Run3_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run3_detvar/overlay_pelee_ntuples_bnb_nu_detvar_run3_WireModThetaYZ_reprocess_ana.root");
	
	// Run4a
	
	WhichSampleArray.push_back("Overlay9_Run4a_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYDown_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Run_4_BNB_Nu_Detvar_LYAttenuation_Pandora_Reco2_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYRayleigh_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_SCE_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Recomb2_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_x_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_yz_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_XZ_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4a_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_YZ_reco2_ana.root");	

	// Run4b
	
	WhichSampleArray.push_back("Overlay9_Run4b_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYDown_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Run_4_BNB_Nu_Detvar_LYAttenuation_Pandora_Reco2_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYRayleigh_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_SCE_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Recomb2_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_x_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_yz_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_XZ_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4b_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_YZ_reco2_ana.root");
	
	// Run4c
	
	WhichSampleArray.push_back("Overlay9_Run4c_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYDown_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Run_4_BNB_Nu_Detvar_LYAttenuation_Pandora_Reco2_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYRayleigh_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_SCE_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Recomb2_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_x_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_yz_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_XZ_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4c_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_YZ_reco2_ana.root");
	

	// Run4d
	
	WhichSampleArray.push_back("Overlay9_Run4d_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Detvar_BNB_nu_pandora_reco2_CV_run4_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYDown_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/Run_4_BNB_Nu_Detvar_LYAttenuation_Pandora_Reco2_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_5_bnb_nu_overlay_detvar_LYRayleigh_reco2_pandora_unified_run4_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_SCE_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Recomb2_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_x_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_wiremod_yz_pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_XZ_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run4d_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run4_detvar/run4_bnb_nu_detvar_Pandora_WireMod_Theta_YZ_reco2_ana.root");
	
	// Run 5
	 
	WhichSampleArray.push_back("Overlay9_Run5_CV"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_DetVar_bnb_CV_Pandora_Unified_reco2_run5_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_CVextra"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_DetVar_bnb_CV_Pandora_Unified_reco2_run5_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_LYDown"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run4_5_bnb_nu_overlay_detvar_LYDown_reco2_pandora_unified_run5_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_LYAttenuation"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/Run_5_BNB_Nu_Detvar_LYAttenuation_Pandora_Reco2_run5_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_LYRayleigh"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run4_5_bnb_nu_overlay_detvar_LYRayleigh_reco2_pandora_unified_run5_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_SCE"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_bnb_nu_detvar_SCE_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_Recombination2"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_bnb_nu_detvar_Recomb2_pandora_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_X"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_bnb_nu_detvar_wire_mod_x_Pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_YZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_bnb_nu_detvar_wire_mod_yz_Pandora_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_ThetaXZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_bnb_nu_detvar_Pandora_WireMod_Theta_XZ_reco2_reco2_ana.root");
	WhichSampleArray.push_back("Overlay9_Run5_ThetaYZ"); SamplePath.push_back("/pnfs/uboone/persistent/users/cthorpe/PELEE_2023/run5_detvar/run5_bnb_nu_detvar_Pandora_WireMod_Theta_YZ_reco2_reco2_ana.root");
	
	// ---------------------------------------------------------------------------------- //
	// ---------------------------------------------------------------------------------- //


	gROOT->ProcessLine(".L ../myClasses/Tools.cxx+");
	gROOT->ProcessLine(".L ../myClasses/STV_Tools.cxx+");	

	gROOT->ProcessLine(".L neutrino_selection.cxx+");

	for (int i = 0;i < (int)(WhichSampleArray.size()); i++) {

			gROOT->ProcessLine("neutrino_selection(\""+WhichSampleArray[i]+"\",\""+SamplePath[i]+"\").Loop()");

	}

	gROOT->ProcessLine(".q");

};
