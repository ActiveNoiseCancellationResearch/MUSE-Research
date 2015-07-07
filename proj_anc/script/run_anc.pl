# Usage: run_anc <master_cfg_filename>

use strict;
use warnings;
use File::Path;
use File::Copy;
use File::Spec;

# Enables command window to be accessed by Perl
$ENV{PATH} .= ";C:\\windows\\command".";c:\\windows\\system32".";c:\\winnt\\system32";

my $proj_root;
my @split_list;
my @tmp_arr;
my $tmp_str;
my $cfg_filename;
my $master_cfg_filename_root = $ARGV[0];

    # Add cfg filepath to the command line argument specifying the cfg filename
    my $master_cfg_filename = "..\\model\\cfg\\${master_cfg_filename_root}.m";

    # Pull the %PROJ_ANC% environment variable (user must set this variable by configuring Windows)
    $proj_root = $ENV{"PROJ_ANC"};

    # Path to copy all cfg and source files to exp directory
    my $exp_subdirectory = "$proj_root\\exp\\$master_cfg_filename_root";
   
    
    print( "\n" );
    print( "============================================================================\n" );
    print( "Master Configuration File is at: ${master_cfg_filename}\n" );
    print( "Project ROOT is at: ${proj_root}\n" );
    print( "============================================================================\n" );
    print( "\n" );
    
    open (my $fh, '<', $master_cfg_filename)
        or die "Could not open file '$master_cfg_filename' $!";
       
    # Create subfolder under exp named after the master cfg file 
    system( "mkdir $exp_subdirectory");

    # Copy the master cfg into the newly created subfolder and renaming to standardize the master cfg file
    copy($master_cfg_filename, "$exp_subdirectory/master_cfg.m");
    
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
                #print "\t$cfg_filename\n";
                
                # Create subfolder under exp named after the master cfg file 
                system( "mkdir $exp_subdirectory");
               
                # Copy the cfg files into the newly created subfolder
                copy($cfg_filename, $exp_subdirectory);
                                
            }
        }
    }  
    
    closedir($fh);

# Add src filepath to the command line argument specifying the src filename
my $source_filename = "..\\model\\src\\";

    opendir (my $DIR, $source_filename)
        or die "can't opendir $source_filename: $!";  
    
    # All files are read from the source directory that is open
    my @files = readdir($DIR);

    # For each of the files in the directory, they are copied and placed into the exp subdirectory
    foreach my $t (@files)
    {
       # If file is a plain file in the src directory
       if(-f "$source_filename/$t" ) {
          
          copy ("$source_filename/$t", "$exp_subdirectory/$t");
       }
    }
    closedir($DIR);


