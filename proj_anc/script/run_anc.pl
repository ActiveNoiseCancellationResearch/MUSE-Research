# Usage: run_anc <master_cfg_filename>

use strict;
use warnings;

my $master_cfg_filename;
my $proj_root;
my @split_list;
my @tmp_arr;
my $tmp_str;
my $cfg_filename;

    # Add cfg filepath to the command line argument specifying the cfg filename
    $master_cfg_filename = "..\\model\\cfg\\$ARGV[0]";
    
    # Pull the %PROJ_ROOT% environment variable (user must set this variable by configuring Windows)
    $proj_root = $ENV{"PROJ_ANC"};
    
    print( "\n" );
    print( "============================================================================\n" );
    print( "Master Configuration File is at: ${master_cfg_filename}\n" );
    print( "Project ROOT is at: ${proj_root}\n" );
    print( "============================================================================\n" );
    print( "\n" );
    
    open my $fh, '<', $master_cfg_filename
        or die "Could not open file '$master_cfg_filename' $!";
 
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
                $cfg_filename = "$cfg_filename.m";
                print "$cfg_filename\n";
            }
        }
    }        
    