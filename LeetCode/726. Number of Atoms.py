from collections import defaultdict


class Solution:

    def isUpper(self, c):
        return ord(c) >= ord('A') and ord(c) <= ord('Z')

    def isLower(self, c):
        return ord(c) >= ord('a') and ord(c) <= ord('z')

    def isNumber(self, c):
        return ord(c) >= ord('0') and ord(c) <= ord('9')

    def getAtomName(self):
        atom_name = self.formula[self.pos]
        self.pos += 1
        while self.pos < len(self.formula) and self.isLower(self.formula[self.pos]):
            atom_name += self.formula[self.pos]
            self.pos += 1
        print('get atom ', atom_name)
        return atom_name

    def getNumber(self):
        ret = 0
        while self.pos < len(self.formula) and self.isNumber(self.formula[self.pos]):
            ret = ret * 10 + int(self.formula[self.pos])
            self.pos += 1
        print('get number ', ret)
        return ret

    def parseFormula(self):

        ret = defaultdict(int)

        while self.pos < len(self.formula):
            if self.formula[self.pos] == ')':
                # the end of parentheses expression
                self.pos += 1
                return ret
            cur = self.formula[self.pos]
            if self.isUpper(cur):
                atom_name = self.getAtomName()
                atom_count = 1
                if self.pos < len(self.formula) and self.isNumber(self.formula[self.pos]):
                    atom_count = self.getNumber()
                ret[atom_name] += atom_count
            elif cur == '(':
                self.pos += 1
                sub_formula_ret = self.parseFormula()
                atom_count = 1
                if self.pos < len(self.formula) and self.isNumber(self.formula[self.pos]):
                    atom_count = self.getNumber()
                for atom_name, count in sub_formula_ret.items():
                    ret[atom_name] += count * atom_count

        print('get count', ret)
        return ret

    def countOfAtoms(self, formula):
        """
        :type formula: str
        :rtype: str
        """
        self.pos = 0
        self.formula = formula
        ret = self.parseFormula()
        output = []
        counts = list(ret.items())
        counts.sort()
        for val in counts:
            output.append(val[0])
            if val[1] > 1:
                output.append(str(val[1]))
        return ''.join(output)
