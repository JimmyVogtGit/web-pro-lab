import { binarySearch } from "./exercice-a1";

describe("recherche linéaire vs recherche linéaire", () => {
  it("Doit retourner -1 si le taleau est vide", () => {
    expect(binarySearch([], 1)).toBe(-1);
  });
});
