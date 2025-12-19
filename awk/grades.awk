command to run 
awk -f grade.awk students.txt

function getGrade(marks, max) {
    # grading per subject (out of 50)
    if (marks >= 45) return "O"
    else if (marks >= 40) return "A"
    else if (marks >= 35) return "B"
    else if (marks >= 25) return "C"
    else return "F"
}

function getOverallGrade(total) {
    # cumulative grading (out of 250)
    if (total >= 200) return "O"
    else if (total >= 170) return "A"
    else if (total >= 150) return "B"
    else if (total >= 125) return "C"
    else return "F"
}

BEGIN {
    FS=","; OFS=","
    # Print headers
    printf "%-8s %-12s %-6s %-6s %-6s %-6s %-6s %-8s %-6s %-6s\n", \
           "RollNo", "Name", "OS", "DAA", "SE", "CD", "MOOC", "Total", "Grade", "Result"
    print "--------------------------------------------------------------------------------------"
}

NR > 1 {
    os = $5; daa = $6; se = $7; cd = $8; mooc = $9
    total = os + daa + se + cd + mooc

    # individual subject grades
    osg = getGrade(os, 50)
    daag = getGrade(daa, 50)
    seg = getGrade(se, 50)
    cdg = getGrade(cd, 50)
    moocg = getGrade(mooc, 50)

    # overall grade
    grade = getOverallGrade(total)

    # result
    result = (grade == "F") ? "Fail" : "Pass"

    # print row
    printf "%-8s %-12s %-6s %-6s %-6s %-6s %-6s %-8d %-6s %-6s\n", \
           $2, $3, osg, daag, seg, cdg, moocg, total, grade, result
}
