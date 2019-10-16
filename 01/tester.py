import subprocess

def check(expression,result):
    out = subprocess.run(['./main',expression],stdout=subprocess.PIPE)
    if out.stdout != result:
        print('error {0} != {1}, got {2}'.format(expression,result,out.stdout))
    else:
        print('OK')
        
#receiving binary strings from cpp binary file         
print("Start testing:")
check(b'-2/12 + 2332/---2 + 21/-3 - 12',b'-1185.17')
check(b'1213-123/123 + 123-23*123*13 - 123 + 123 - 0 - 1/2',b'-35442.5')
check(b'--12 - 34 - 34 + 1223 - 213--34 / 34',b'955')
check(b'--12 - 34 - 34 + 1223 - 213--34 / 34',b'955')
check(b'1+2+3+4/5/6/7/8/9-10-11--12---13----14-----15*16*17*18*19/--7',b'-199339')
check(b'-0/-2 +987/654 - 123*9/8 -- -12/3',b'-140.866')