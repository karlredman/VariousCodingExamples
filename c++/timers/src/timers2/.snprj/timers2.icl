b1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           XX����p		#display files in groups
			
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
		set Undo_files_to_unload $x_Undo_files_to_unload
		set Undo_ProjectFiles    $x_Undo_ProjectFiles
		
		Display_ProjectFiles
	}
	
	proc can_create_project {prjdir prjname} {
		set name [sn_build_project_filename $prjdir $prjname]
		
		if {[sn_is_project_busy $name in remuser remhost port] != ""} {
			sn_error_dialog [format [get_indep String PafProjBusy]  $name "${remuser}@${remhost}"]
			return 0
		}
		
		if {[file exists $name]} {
			set answer [tk_dialog auto  [get_indep String FileExists]  $name  question_image  0  [get_indep String Overwrite]  [get_indep String cancel]]
			if {$answer == 1} {
				return 0
			} else {
				#delete existing project
				set ret [sn_delete_project $name]
				#unable to delete the project
				if {$ret == 0} {
					sn_error_dialog [get_indep String CannotDeleteProject]
					return 0
				}
			}
		}
		return 1
	}
	method apply {{exit ""}} {
		global sn_options
		global sn_newargs
		
		upvar #0 $this-view view
		if {$view == ""} {
			@@set view "default"
		}
		set CurrentView $view
		
		if {$new_project} {
			set prjdir  [file dirname [sn_filecmd format -sn $sn_newargs(path)]]
			set prjname [file tail    [sn_filecmd format -sn $sn_newargs(path)]]
			
			#valid project name ??
			if {$prjname == ""} {
				sn_error_dialog [get_indep String InvalidProjectName]
				focus [$prjname_Entry entry]
				return
			}
			
			#valid project name ??
			if {[catch {set realprjdir [realpath -pwd [pwd] $prjdir]} err]} {
				sn_error_dialog "$prjdir: $err"
				focus [$prjname_Entry entry]
				return
			}
			
			#Does the directory exist?
			if {![file isdirectory $prjdir]} {
				sn_error_dialog [get_indep String InvalidProjectDir]
				focus [$prjdir_Entry entry]
				return
			}
			
			#verify if the file exists or is being used
			if {! [can_create_project $realprjdir $prjname]} {
				return
			}
			#now we can set project file
			@@set sn_options(sys,project-file) [sn_filecmd format  -sn $sn_newargs(path)]
		
			#project directory can be only changed by new projects
			#a       Makefile. # 
	       timertest.cc. # je       hardware_timer.h. #  n       hardware_timer.cc. # 	       mytimers.cc. # den       mytimers.h. # 