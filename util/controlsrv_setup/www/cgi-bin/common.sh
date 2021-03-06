# Common functions for Bash CGI
# Author: MJB Authored: 06-12-19
# Include at the top of all CGI scripts.

# WriteParagraph
function wP {
	echo "<p>$1</p>"
}

# WriteHeader format: TEXT HEADER_LEVEL (def. 1)
function wH {
    echo "<h${2:-1}>$1</h${2:-1}>"
}

# Necessary for the CGI wrapper to serve HTML
function writeHeader {
    echo -e 'Content-type: text/html\n'
}

function writeJSONHeader {
    echo -e 'Content-type: application/json\n'
}

#JSON TAG
function jT {
    echo -n "\"$1\":"
}

#JSON FIELD
function jF {
    # JSON expects a comma after each field until the final
    if [ "$2" = "f" ]; then
        echo "\"$1\""
    else
        echo "\"$1\","
    fi
}
