within FMU_Import;

block controlledElectricDrive
  extends FMI.Internal.FMU;

  import FMI.FMI2.Types.*;
  import FMI.FMI2.Interfaces.*;
  import FMI.FMI2.Functions.*;

  package Types
    extends Modelica.Icons.TypesPackage;

    type Modelica.Blocks.Types.Init = enumeration(
      NoInit "No initialization (start values are used as guess values with fixed=false)", 
      SteadyState "Steady state initialization (derivatives of states are zero)", 
      InitialState "Initialization with initial states", 
      InitialOutput "Initialization with initial outputs (and steady state of the states if possible)"
    );

    connector Modelica.Blocks.Types.InitInput = input Modelica.Blocks.Types.Init "'input Modelica.Blocks.Types.Init' as connector" annotation (
      defaultComponentName="u",
      Icon(graphics={Polygon(
            points={{-100,100},{100,0},{-100,-100},{-100,100}},
            lineColor={255,127,0},
            fillColor={255,127,0},
            fillPattern=FillPattern.Solid)}, coordinateSystem(
          extent={{-100,-100},{100,100}},
          preserveAspectRatio=true,
          initialScale=0.2)),
      Diagram(coordinateSystem(
          preserveAspectRatio=true,
          initialScale=0.2,
          extent={{-100,-100},{100,100}}), graphics={Polygon(
            points={{0,50},{100,0},{0,-50},{0,50}},
            lineColor={255,127,0},
            fillColor={255,127,0},
            fillPattern=FillPattern.Solid), Text(
            extent={{-10,85},{-10,60}},
            textColor={255,127,0},
            textString="%name")}));

    connector Modelica.Blocks.Types.InitOutput = output Modelica.Blocks.Types.Init "'output Modelica.Blocks.Types.Init' as connector" annotation (
      defaultComponentName="y",
      Icon(coordinateSystem(
          preserveAspectRatio=true,
          extent={{-100,-100},{100,100}}), graphics={Polygon(
            points={{-100,100},{100,0},{-100,-100},{-100,100}},
            lineColor={255,127,0},
            fillColor={255,255,255},
            fillPattern=FillPattern.Solid)}),
      Diagram(coordinateSystem(
          preserveAspectRatio=true,
          extent={{-100,-100},{100,100}}), graphics={Polygon(
            points={{-100,50},{0,0},{-100,-50},{-100,50}},
            lineColor={255,127,0},
            fillColor={255,255,255},
            fillPattern=FillPattern.Solid), Text(
            extent={{30,110},{30,60}},
            textColor={255,127,0},
            textString="%name")}));

    function Modelica.Blocks.Types.InitToInteger

      input Modelica.Blocks.Types.Init enumerationValue;

      output FMI2Integer integerValue;

    algorithm

      if enumerationValue == Modelica.Blocks.Types.Init.NoInit then
        integerValue := 1;
      elseif enumerationValue == Modelica.Blocks.Types.Init.SteadyState then
        integerValue := 2;
      elseif enumerationValue == Modelica.Blocks.Types.Init.InitialState then
        integerValue := 3;
      elseif enumerationValue == Modelica.Blocks.Types.Init.InitialOutput then
        integerValue := 4;
      else
        assert(false, "Illegal value");
      end if;

    end Modelica.Blocks.Types.InitToInteger;

    function IntegerToModelica.Blocks.Types.Init

      input FMI2Integer integerValue;

      output Modelica.Blocks.Types.Init enumerationValue;

    algorithm

      if integerValue == 1 then
        enumerationValue := Modelica.Blocks.Types.Init.NoInit;
      elseif integerValue == 2 then
        enumerationValue := Modelica.Blocks.Types.Init.SteadyState;
      elseif integerValue == 3 then
        enumerationValue := Modelica.Blocks.Types.Init.InitialState;
      elseif integerValue == 4 then
        enumerationValue := Modelica.Blocks.Types.Init.InitialOutput;
      else
        assert(false, "Illegal value");
      end if;

    end IntegerToModelica.Blocks.Types.Init;

  end Types;


  parameter Modelica.Units.SI.Time communicationStepSize = 1e-2 annotation(Dialog(tab="FMI", group="Parameters"));

  parameter FMI2Real stepV_height(unit="rad/s") = 10 "Height of step";

  parameter FMI2Real stepV_offset(unit="rad/s") = 0 "Offset of output signal y";

  parameter FMI2Real stepV_startTime(unit="s", quantity="Time") = 0.1 "Output y = offset for time < startTime";

  parameter FMI2Real idealGear_ratio(unit="1") = 10 "Transmission ratio (flange_a.phi/flange_b.phi)";

  parameter FMI2Real stepTau_height(unit="N.m") = 3 "Height of step";

  parameter FMI2Real stepTau_offset(unit="N.m") = 0 "Offset of output signal y";

  parameter FMI2Real stepTau_startTime(unit="s", quantity="Time") = 0.5 "Output y = offset for time < startTime";

  parameter FMI2Real PI_k(unit="Wb/rad") = 0.1 "Gain";

  parameter FMI2Real PI_T(unit="s", quantity="Time") = 0.005 "Time Constant (T>0 required)";

  parameter FMI2Real PI_x_start(unit="rad/s") = 0 "Initial or guess value of state";

  parameter FMI2Real PI_y_start(unit="V") = 0 "Initial value of output";

  parameter FMI2Real loadInertia1_J(unit="kg.m2", quantity="MomentOfInertia") = 1 "Moment of inertia";

  parameter FMI2Real dcpm_TaOperational(unit="K", quantity="ThermodynamicTemperature") = 293.15 "Operational armature temperature";

  parameter FMI2Real dcpm_fixed_phi0(unit="rad", quantity="Angle") = 0 "Fixed offset angle of housing";

  parameter FMI2Real dcpmData_Jr(unit="kg.m2", quantity="MomentOfInertia") = 0.001 "Rotor's moment of inertia";

  parameter FMI2Real dcpmData_VaNominal(unit="V", quantity="ElectricPotential") = 100 "Nominal armature voltage";

  parameter FMI2Real dcpmData_IaNominal(unit="A", quantity="ElectricCurrent") = 100 "Nominal armature current (>0..Motor, <0..Generator)";

  parameter FMI2Real dcpmData_wNominal(unit="rad/s", quantity="AngularVelocity") = 149.22565104552 "Nominal speed";

  parameter FMI2Real dcpmData_TaNominal(unit="K", quantity="ThermodynamicTemperature") = 293.15 "Nominal armature temperature";

  parameter FMI2Real dcpmData_Ra(unit="Ohm", quantity="Resistance") = 0.05 "Armature resistance at TaRef";

  parameter FMI2Real dcpmData_TaRef(unit="K", quantity="ThermodynamicTemperature") = 293.15 "Reference temperature of armature resistance";

  parameter FMI2Real dcpmData_alpha20a(unit="1/K", quantity="LinearTemperatureCoefficient") = 0 "Temperature coefficient of armature resistance";

  parameter FMI2Real dcpmData_La(unit="H", quantity="Inductance") = 0.0015 "Armature inductance";

  parameter FMI2Real dcpmData_frictionParameters_power_w(unit="1") = 2 "Exponent of friction torque w.r.t. angular velocity";

  parameter FMI2Real dcpmData_strayLoadParameters_power_w(unit="1") = 1 "Exponent of stray load loss torque w.r.t. angular velocity";

  FMI2RealOutput w(unit="rad/s") annotation(Placement(transformation(extent={ { 100, -10 }, { 120, 10 } }), iconTransformation(extent={ { 100, -10 }, { 120, 10 } })));

protected

  parameter Boolean startValuesSet(start=false, fixed=false);

  Boolean initialized(start=false, fixed=true);

  record OutputVariables
    Real w;
  end OutputVariables;

  OutputVariables outputVariables;

initial algorithm

  FMI.Internal.loadFMU(
    instance=instance,
    unzipdir=Modelica.Utilities.Files.loadResource("modelica://FMU_Import/Resources/FMUs/342b9e3"),
    fmiVersion=2,
    modelIdentifier="ControlledElectricDrive_FMU_2",
    instanceName=getInstanceName(),
    interfaceType=1,
    instantiationToken="{0676815a-bc72-45f8-b01e-dd68577a9366}",
    visible=visible,
    loggingOn=loggingOn,
    logFMICalls=logFMICalls,
    logToFile=logToFile,
    logFile=logFile,
    copyPlatformBinary=false);

  FMI.Internal.Logging.logMessages(instance);

  if not startValuesSet then
    startTime := time;
    FMI2SetReal(instance, valueReferences={16777216}, nValues=1, values={stepV_height});
    FMI2SetReal(instance, valueReferences={16777217}, nValues=1, values={stepV_offset});
    FMI2SetReal(instance, valueReferences={16777218}, nValues=1, values={stepV_startTime});
    FMI2SetReal(instance, valueReferences={16777219}, nValues=1, values={idealGear_ratio});
    FMI2SetReal(instance, valueReferences={16777220}, nValues=1, values={stepTau_height});
    FMI2SetReal(instance, valueReferences={16777221}, nValues=1, values={stepTau_offset});
    FMI2SetReal(instance, valueReferences={16777222}, nValues=1, values={stepTau_startTime});
    FMI2SetReal(instance, valueReferences={16777223}, nValues=1, values={PI_k});
    FMI2SetReal(instance, valueReferences={16777224}, nValues=1, values={PI_T});
    FMI2SetReal(instance, valueReferences={16777225}, nValues=1, values={PI_x_start});
    FMI2SetReal(instance, valueReferences={16777226}, nValues=1, values={PI_y_start});
    FMI2SetReal(instance, valueReferences={16777227}, nValues=1, values={loadInertia1_J});
    FMI2SetReal(instance, valueReferences={16777228}, nValues=1, values={dcpm_TaOperational});
    FMI2SetReal(instance, valueReferences={16777229}, nValues=1, values={dcpm_fixed_phi0});
    FMI2SetReal(instance, valueReferences={16777230}, nValues=1, values={dcpmData_Jr});
    FMI2SetReal(instance, valueReferences={16777231}, nValues=1, values={dcpmData_VaNominal});
    FMI2SetReal(instance, valueReferences={16777232}, nValues=1, values={dcpmData_IaNominal});
    FMI2SetReal(instance, valueReferences={16777233}, nValues=1, values={dcpmData_wNominal});
    FMI2SetReal(instance, valueReferences={16777234}, nValues=1, values={dcpmData_TaNominal});
    FMI2SetReal(instance, valueReferences={16777235}, nValues=1, values={dcpmData_Ra});
    FMI2SetReal(instance, valueReferences={16777236}, nValues=1, values={dcpmData_TaRef});
    FMI2SetReal(instance, valueReferences={16777237}, nValues=1, values={dcpmData_alpha20a});
    FMI2SetReal(instance, valueReferences={16777238}, nValues=1, values={dcpmData_La});
    FMI2SetReal(instance, valueReferences={16777239}, nValues=1, values={dcpmData_frictionParameters_power_w});
    FMI2SetReal(instance, valueReferences={16777240}, nValues=1, values={dcpmData_strayLoadParameters_power_w});
    FMI2SetupExperiment(instance,
      toleranceDefined=tolerance > 0.0,
      tolerance=tolerance,
      startTime=startTime,
      stopTimeDefined=stopTime < Modelica.Constants.inf,
      stopTime=stopTime);
    FMI2EnterInitializationMode(instance);
    startValuesSet := true;
  end if;

algorithm

  when {initial(), sample(startTime, communicationStepSize)} then


    if not initialized and not initial() then
      FMI2ExitInitializationMode(instance);
      initialized := true;
    end if;

    if time >= startTime + communicationStepSize then
      FMI2DoStep(instance,
        currentCommunicationPoint=time - communicationStepSize,
        communicationStepSize=communicationStepSize,
        noSetFMUStatePriorToCurrentPoint=true);
    end if;

    if not initial() then
      outputVariables.w := FMI2GetReal(instance, valueReference=603979776);
    end if;

  end when;

equation

  if initial() then
    w = pure(FMI2GetInitialReal(instance, startTime, valueReference=603979776));
  else
    w = outputVariables.w;
  end if;

  annotation (
   Icon(coordinateSystem(
      preserveAspectRatio=false,
      extent={{-100,-100},{100,100}}),
      graphics={Bitmap(extent={{-90,-90},{90,90}}, fileName="modelica://FMI/Resources/Images/FMU_bare.svg")}
    ),
    Diagram(coordinateSystem(preserveAspectRatio=false, extent={{-100,-100},{100,100}})),
    experiment(StopTime=1.0),
    uses(FMI(version="0.0.9")),
    Documentation(info="<html>
<p>For more information open the FMU's <a href=\"modelica://FMU_Import/Resources/FMUs/342b9e3/documentation/index.html\">original documentation</a>.</p>
</html>")
  );
end controlledElectricDrive;