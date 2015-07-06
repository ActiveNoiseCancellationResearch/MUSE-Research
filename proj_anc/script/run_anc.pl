# Usage: run_anc <master_cfg_filename>

use strict;
use warnings;
use File::Path;
use File::Copy;
use File::Spec;

$ENV{PATH} .= ";C:\\windows\\command".";c:\\windows\\system32".";c:\\winnt\\system32";

my $master_cfg_filename;
my $proj_root;
my @split_list;
my @tmp_arr;
my $tmp_str;
my $cfg_filename;
my $master_cfg_filename_root = $ARGV[0];

    # Add cfg filepath to the command line argument specifying the cfg filename
    $master_cfg_filename = "..\\model\\cfg\\${master_cfg_filename_root}.m";
    
    # Pull the %PROJ_ANC% environment variable (user must set this variable by configuring Windows)
    $proj_root = $ENV{"PROJ_ANC"};
    
    print( "\n" );
    print( "============================================================================\n" );
    print( "Master Configuration File is at: ${master_cfg_filename}\n" );
    print( "Project ROOT is at: ${proj_root}\n" );
    print( "============================================================================\n" );
    print( "\n" );
    
    open my $fh, '<', $master_cfg_filename
        or die "Could not open file '$master_cfg_filename' $!";
    
    my $exp_subdirectory = "$proj_root\\exp\\$master_cfg_filename_root";
    
    # Create subfolder under exp named after the master cfg file 
    system( "mkdir $exp_subdirectory");

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
                $cfg_filename = $proj_root."\\model\\cfg\\"."${cfg_filename}.m";
                print "\t$cfg_filename\n";
                
                # Create subfolder under exp named after the master cfg file 
                system( "mkdir $exp_subdirectory");
               
                # Copy the cfg files into the newly created subfolder
                copy($cfg_filename, $exp_subdirectory);
                                
            }
        }
    }        

