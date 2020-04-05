# MJB 20 11 2019
# Log util: functions to be used in any test script.
# Call these from within another script. Cannot be run 'standalone'.

if [ "$0" = "./logutil.sh" ]; then
    echo "This utility cannot be run standalone."
    exit 1
fi

function formattedDate {
    date +'%F %R'
}

function printFatalError {
    echo "$(formattedDate) Fatal Error: $1"
    exit 1
}
