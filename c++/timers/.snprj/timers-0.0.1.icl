b1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         B   8�P 4h`�� T�����@t���eew  -fileimage file_h_image  -dirimage dir_image  -contents $hfiles  -parent $hi  -basedir $disp_Directories
			}
			
			if {$files_to_unload != ""} {
				set img dir_image
				set ui [$treew insert end  -text [get_indep String UnloadedFiles]  -image $img]
				fill_file_tree  -widget $treew  -fileimage file_d_image  -dirimage dir_image  -contents $ufiles  -parent $ui  -basedir $disp_Directories

			}
		  }
		"list" {
			#display an easy file list
			#delete old entries
			$treew delete 0 end
			
			#add project name as first icon
			$treew insert end  -text [get_indep String ProjectFiles]  -image dir_image
			#$treew insert end list $pfiles -parent 0 -image file_s_image
			add_list_to_project $treew 0 file_s_image $disp_Directories $pfiles
			
			#Hidden files, if availiable
			if {$HiddenFiles != ""} {
				set hi [$treew insert end  -text [get_indep String HiddenFiles]  -image dir_image]
				#$treew insert end list $hfiles -parent $hi -image file_h_image
				add_list_to_project $treew $hi file_h_image $disp_Directories $hfiles
			}
			
			#unloaded files, if availiable
			if {$files_to_unload != ""} {
				set hi [$treew insert end  -text [get_indep String UnloadedFiles]  -image dir_image]
				#$treew insert end list $ufiles -parent $hi -image file_d_image
				add_list_to_project $treew $hi file_h_image $disp_Directories $ufiles
			}
		  }
		"cat" {
			#display files in groups
			
			#get known types and extensions to sort
			set types ""
			foreach type $Avail_Parsers {
				lappend types [list $Parser_Info($type,TYPE) $Parser_Info($type,SUF)]
			}
			set types [@@lsort -dictionary $types]
			
			#delete old entries
			$treew delete 0 end
			
			#add project name as first icon
			$treew insert end  -text [get_indep String ProjectFiles]  -image dir_image
			AddFilesAsCategorie $treew $types 0 $pfiles file_s_image $disp_Directories
			
			#Hidden files, if availiable
			if {$HiddenFiles != ""} {
				set hi [$treew insert end  -text [get_indep String HiddenFiles]  -image dir_image]
				AddFilesAsCategorie $treew $types $hi $hfiles file_h_image $disp_Directories
			}
			
			#unloaded files, if availiable
			if {$files_to_unload != ""} {
				set hi [$treew insert end  -text [get_indep String UnloadedFiles]  -image dir_image]
				AddFilesAsCategorie $treew $types $hi $ufiles file_d_image $disp_Directories
			}
		  }
		}
		
		project_CloseAlreayClosed $treew $Tree_Mode
		
		Tree& @@ resize_widget $treew
		
		watch n
	}
	
	method toggle_disp_mode {} {
		upvar #0 $this-Tree_Mode tm
		
		if {$tm == "tree" } {
			$Toolbar.dirs config -state disabled
		} else {
			$Toolbar.dirs config -state normal
		}
		#change tabs to delete unneeded tabs
		if {$tm == "tree" || $disp_Directories == 0} {
			$tree change_tabs 0 250 Name
		} else {
			$tree change_tabs 1 {250 250} {Name Directory}
		}
		if {$Tree_Mode != $tm} {
			set Tree_Mode $tm
			Display_ProjectFiles
		}
	}
	
	method undo {} {
		#ReadProjectFiles
		set x_Undo_HiddenFiles     $HiddenFiles
		set x_Undo_files_to_unload $files_to_unload
		set x_Undo_ProjectFiles    $ProjectFiles
		
		set ProjectFiles    $Undo_ProjectFiles
		set HiddenFiles     $Undo_HiddenFiles
		set files_to_unload $Undo_files_to_unload
		
		set Undo_HiddenFiles     $x_Undo_HiddenFiles
		set Undo_files_to_unload $x_Undo_files_t       Makefile. # oj       Makefilebin #        Makefilesrc #        Makefilesrc/timers2 #        Timer.hsrc/timers2 # e       mThread.hsrc/timers2 #  $p       Timer.ccsrc/timers2 #        mThread.ccsrc/timers2 # os       timertest.ccsrc/timers2 #        Makefilesrc/timers1 #        Timer.hsrc/timers1 # h       mThread.hsrc/timers1 # fil       Timer.ccsrc/timers1 #        mThread.ccsrc/timers1 # g        timertest.ccsrc/timers1 #        Makefilesrc/timers #         Timer.hsrc/timers # 	i       mThread.hsrc/timers #        Timer.ccsrc/timers # g       mThread.ccsrc/timers # roj       timertest.ccsrc/timers # e       Makefileinclude #        config.hinclude # 