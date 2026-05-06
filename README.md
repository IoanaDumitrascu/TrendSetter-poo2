### TrendSetter 

Proiectul simulează parcursul unui influencer în industria modei, gestionând resursele financiare și stilul personal pentru a atinge succesul în mediul online și la evenimente exclusiviste.

 ### Scopul jocului:
Jucătorul (Influencerul) trebuie să își construiască o garderobă strategică, achiziționând piese vestimentare și accesorii care să îi maximizeze scorul de impact. Obiectivul este acumularea unui punctaj total de stil suficient de mare pentru a debloca accesul la evenimente de prestigiu (Gala, Street-Style, Business) și pentru a câștiga followeri.

### Logica și regulile jocului:

*   **Resurse inițiale:** Influencerul pornește cu un nume și un buget inițial definit de utilizator.
*   **Garderoba:** Este formată din piese vestimentare împărțite în mai multe categorii, fiecare având un impact diferit asupra scorului final:
    *   **Haine:** Piese de bază care oferă bonusuri în funcție de material (ex: mătasea oferă un multiplicator mai mare) și funcționalitate (ex: hainele impermeabile oferă puncte extra).
    *   **Încălțăminte:** Influențează scorul prin nivelul de confort și mărimea potrivită.
    *   **Bijuterii:** Obiecte de lux care aduc punctaje masive în funcție de numărul de carate.
    *   **Accesorii:** Elemente care pot dubla impactul unei ținute dacă sunt marcate ca fiind de "Lux".

*   **Sistemul de achiziții:**
    *   Fiecare piesă are un preț de bază. Dacă bugetul influencerului scade sub prețul piesei dorite, sistemul aruncă o **excepție de buget** și tranzacția este anulată.
    *   Piesele sunt gestionate prin pointeri inteligenți (`std::unique_ptr`), asigurând o gestionare eficientă a memoriei.

*   **Calculul punctajului (Impactul):**
    *   Scorul fiecărei piese se bazează pe un punctaj de stil de bază (1-100) la care se aplică modificatori:
        *   **Material de lux (Mătase/Piele):** Multiplicator de x1.5 sau x1.8.
        *   **Bijuterii:** Punctaj de stil + (Carate * 5).
        *   **Încălțăminte:** Punctaj de stil + (Confort * 2.5).
        *   **Accesorii de lux:** Punctaj dublat (x2).

*   **Evenimente:**
    *   Influencerul poate alege să participe la evenimente (ex: MILAN FASHION WEEK).
    *   Succesul la eveniment depinde de pragul de impact total acumulat în garderobă. Dacă scorul este peste prag, influencerul devine "Viral", altfel ținuta este considerată un eșec.

*   **Persistența datelor:**
    *   Garderoba poate fi exportată într-un fișier extern (`.txt`), permițând salvarea progresului și a istoricului achizițiilor.

### Ierarhia de clase:

*   **Baza (abstractă):** `PiesaVestimentara`
    *   **Derivata 1:** `Haina`
    *   **Derivata 2:** `Incaltaminte`
    *   **Derivata 3:** `Bijuterie`
    *   **Derivata 4:** `Accesoriu`

### Alte clase și mecanisme:

*   **Influencer:** Clasa de gestiune a inventarului și a bugetului.
*   **FashionException:** Ierarhie proprie de excepții (ex: `BudgetExceededException`, `InvalidAttributeException`).
*   **EvaluatorEveniment:** Logică separată pentru validarea succesului în funcție de contextul social.
*   **Clone Pattern:** Metodă virtuală pentru realizarea de "deep copy" polimorfic.
