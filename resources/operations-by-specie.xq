declare variable $inputDocument external;
declare variable $specie_id external;
declare variable $month external;

doc($inputDocument)/species/specie[@id=$specie_id]/operations/operation[@month=$month]
