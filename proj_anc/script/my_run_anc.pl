# Usage: my_run_anc <master_cfg_filename>


use strict;
use warnings;

use File::Find;
use File::Copy;

my $dir = "/tmp"

sub process_file
{
    if($File::Find::dir ne $dir)
    {
        $File::Find::prune = 1;
        return 0;
    }

    return 0 if ($_ !~ /\.m$/);

    copy($File::Find::name, "/tmp/foo/$_")
    or die "Failed to copy $_: $!\n";

    return 1;
}

find(\&process_file, $dir);