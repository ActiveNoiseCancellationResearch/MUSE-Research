# Usage: run_anc <master_cfg_filename> <mu> {-f}

use strict;
use warnings;
use File::Path;
use File::Copy;
use File::Spec::Functions;

# Enables command window to be accessed by Perl
$ENV{PATH} .= ";C:/windows/command".";c:/windows/system32".";c:/winnt/system32".";c:/matlab/bin";
    my $proj_root;
    my @split_list;
    my @tmp_arr;
    my $tmp_str;
    my $cfg_filename;
    my $master_cfg_filename_root = $ARGV[0];
    my $mu = $ARGV[1];
    my $option = $ARGV[2];
    my $result;

    # Add cfg filepath to the command line argument specifying the cfg filename
    my $master_cfg_filename = catfile("../model/cfg","${master_cfg_filename_root}.m");

    # Pull the %PROJ_ANC% environment variable (user must set this variable by configuring Windows)
    $proj_root = $ENV{"PROJ_ANC"};

   # Path to copy all cfg and source files to exp directory
    my $exp_subdirectory = catdir($proj_root, "exp", $master_cfg_filename_root);
    
    print( "\n" );
    print( "============================================================================\n" );
    print( "Master Configuration File is at:    ${master_cfg_filename}\n" );
    print( "Project ROOT is at:                 ${proj_root}\n" );
    print( "Experiment subdirectory is at:      ${exp_subdirectory}\n" );
    print( "============================================================================\n" );
    print( "\n" );
    
    open (my $fh, '<', $master_cfg_filename)
        or die "Could not open file '$master_cfg_filename' $!";
       
    if (-e $exp_subdirectory)
    {
        if (defined $option && $option eq "-f") 
        {
            print("\nDirectory exists, overwriting results\n");
        }
        else
        {
            print("\nThis directory/experiment already exists\n");
            die;
        }
    }

    # Create subfolder under exp named after the master cfg file 
    my $sys_cmd = "mkdir ${exp_subdirectory}";
    print( "\nRunning:\n\n${sys_cmd}\n\n   " );
    system($sys_cmd);

    # Copy the master cfg into the newly created subfolder and renaming to standardize the master cfg file
    copy($master_cfg_filename, catfile("$exp_subdirectory", "master_cfg.m") )
        or die "\nFailed to copy master_cfg.m to ${exp_subdirectory}\n";
    
    # Step through each line of the master cfg file
    while (<$fh>) 
    {
        # Strip out the newline characters
        chomp;
        
        # Parse for the % character, which is the Matlab comment, only consider the text before the first %
        @split_list = split('%', $_);
        
        if (defined $split_list[0])
        {
            # Remove the ; character, if any, and any following text
            @tmp_arr = split( ';', $split_list[0] );

            # Capture any leading white space in $1, then actual non-white text into $2        
            $tmp_arr[0] =~ /(\s*)([\w\._]+)/;
            
            # Append the .m extension, to get the filename
            $cfg_filename = $2;
            
            if (defined $cfg_filename)
            {
                $cfg_filename = catfile( "$proj_root", "/model/cfg", "${cfg_filename}.m");
                print( "\n\nAbout to copy $cfg_filename to $exp_subdirectory \n\n");
                # Copy the cfg files into the newly created subfolder
                copy($cfg_filename, $exp_subdirectory)
                    or die "\nFailed to copy to ${exp_subdirectory}\n";
                                
            }
        }
    }  
    
    close($fh);

    open(my $fhh, '>>', $master_cfg_filename)
        or die "Could not open and append  to file '$master_cfg_filename' $!";

    say $fhh "mu = $mu";
   
    close($fhh); 

    # Add src filepath to the command line argument specifying the src filename
    my $source_dir = catdir("../model", "src");

    # Open src directory
    opendir (my $DIR, $source_dir)
        or die "can't opendir $source_dir: $!";  
    
    # All files are read from the src directory
    my @files = readdir($DIR);

    # For each of the files in the directory, they are copied and placed into the exp subdirectory
    foreach my $t (@files)
    {
        my $src_file;
        
        $src_file = catfile( $source_dir, $t );
        
        # If file is a plain file in the src directory
        if(-f $src_file )
        {
            copy ($src_file, "$exp_subdirectory");
        }
    }
    closedir($DIR);
         
    # Create new string variable that will be read by the matlab shell
    # Make sure no spaces in string file or matlab will not ignore anything after space
     
    #    my $matlabcom = "matlab -r "."pwd='$exp_subdirectory';cd(pwd);ANC_Model";
    my $matlabcom = "matlab -nosplash -nodesktop -noFigureWindows -r "."pwd='$exp_subdirectory';cd(pwd);ANC_Model";
            
    # Run the ANC_Model file within the new subfolder
    print( "\nRunning:\n\n${matlabcom}\n\n   " );
    system($matlabcom);
